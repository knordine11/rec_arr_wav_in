#include "fftstuff.h"
#include <iostream>
#include "fftw3/fftw3.h"
#include "qdebug.h"
#include <cmath>
#include <iomanip>

using namespace std;

double temp_freq = 0;   // temp used for testing only
// double rec_arr[1000000];
int frame_start = 0;
int frame_size = 2048;
int frame_end = frame_start + frame_size;

double Fs = 44100;
const int N = 16384*4; // 2^14 * 4 =  2^16 = 65,536
double bin_size = Fs/N;

fftw_complex* in, * out;
double last_peak = 0;
double peak_val = 0;
double peak_f_bin = 0;
double peak_diff = 0;

double lev1 = 0;
double lev2 = 0;
double lev3 = 0;

double TlevL = 0;
double TlevH = 0;

double levA = 0;


double move_by = 0;
double freq_got =0;
bool Flag_up = true;

FftStuff::FftStuff(QObject *parent)
    : QObject{parent} { }

void FftStuff:: make_sin(double freq ,int beg, int leng){
    double Pi = 3.14159265358979323846;
    int i = beg;
    int en = leng+beg;
    temp_freq = freq;
    cout << endl << "--------( " << freq << " Hz )-- " << beg <<" { make_sin  } " << en << endl;    
    while (i < en) {
        rec_arr[i] = sin(2 * Pi * freq * i /44100 ) ;
        i=i+1;
    }
}

void FftStuff::look_rec_arr(int beg, int end)
{
    cout << endl << "------------->    " << beg  << " { look_rec_arr  } " << end << endl;
    int i = beg;
    while (i < end) {
        cout << i << " >  " << rec_arr[i]<<endl;
        i++;
    }
    cout <<"             END IN INPUT     START OF OUTPUT"<<endl;
}

void FftStuff::DoIt(int beg, int lengh)
{
    qDebug() << ">>>>> called Doit";
    fftw_plan p;
    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);    

    int at=beg;
    int end_at = beg+lengh;

    for (int i = 0; i < N; i++)
    {
        if(i<end_at)
        {
            in[i][0] = rec_arr[at];
            at++;
        }
        else
        {
            in[i][0] = 0.0;
        }
        in[i][1] = 0.0;    
    }
    fftw_execute(p); /* repeat as needed */


    std::cout << std::fixed;
    std::cout << std::setprecision(5);

    // UES THIS AS A WAY TO FILL THE FREQUNCY ARRAY WITH ABS CORECTED
    //  TRUE MAX FREQ LIST    IS DERIVED FROM THE FREQUNCY ARRAY
    // THEN PROSSED TO GET THE FUNDAMANTAL FREQ
    // OCT AND NOTE ARE GOTTON FROM THE FUNDAMANTAL FREQ

    for (size_t i = 0; i < N; i++)
    {
        if(i<6000){
            // double cur_bin = bin_freq(i, N, Fs);
            double cur_bin = i * Fs/N;
            // std::cout<<i<<"  " << bin_freq(i, N, Fs) << " Hz : " << abs(out[i]) << std::endl;}
            // std::cout<<i<<"  " << cur_bin << " Hz : " << abs(out[i]) << std::endl;
        }

    }
    // PROCESSES FFT OUTPUT AND GET TRUE PEAKS
    cout << endl << "  got here    PROCESSES FFT OUTPUT   AND GET TRUE PEAKS "<<endl<<endl;

    Flag_up = true;
    double peak = 0;
    peak_val = 0;
    double last_lev = 0;
    int last_peak = 0;
    double last_peak_val =0;
    bool up = true;
    bool peak_looking = true;
    double highest_val = 0;
    double peak_capture = 0.0;

    for(int i = 20; i<6000; i++){
        double val_out = abs(out[i]);
        // cout << i <<" ll "<< last_lev<<" vo "<<val_out <<endl<<endl;
        if(highest_val<last_lev){
            highest_val = last_lev;
            int peak = i-1;
            peak_capture = peak;
        }
        if(up)
        {
            if(last_lev > val_out)
            { // peak found @ i-1
                // int peak = i-1;
                // cout<< " FOUND PEAK AT  BIN  "<< peak <<"  :  " << last_lev << endl;

                if(peak_looking)
                {
                    if(last_peak_val>last_lev){
                        cout << "    TRUE PEAK AT  { BIN "<< last_peak << " }  level "<< last_peak_val
                             <<endl;
                        bin_to_freq(last_peak);
                        peak_looking = false;
                    }
                }
                last_peak_val = last_lev;
                last_peak = i-1;
                up = false;
            }
        }
        else {  // not going up     DOWN
            if(last_lev < val_out)  // found bottom
            {
                up = true;
            }
        }
        last_lev = val_out;
    }
    cout << "bin :" << peak_capture << "max = " << highest_val << endl;
    cout <<endl<< "    ----- AT END OF   DOIT --------" <<endl;
}

double FftStuff::abs(fftw_complex c)
{
    return std::sqrt(c[0] * c[0] + c[1] * c[1]);
}

void FftStuff::bin_to_freq(int bin){

    double bin_freq = bin*bin_size;
    double lev_l = abs(out[bin-1]);
    double lev_ = abs(out[bin]);
    double lev_h = abs(out[bin+1]);

    double bin_l = bin-1;
    double bin_ = bin;
    double bin_h = bin+1;

    double bin_la = bin_l/bin_;
    double bin_ha = bin_h/bin_;

    double bin_lb = 1-bin_la;
    double bin_hb = 1-bin_ha;

    double bin_lc = bin_lb/2;
    double bin_hc = bin_hb/2;

    double bin_ld = bin_lc+1;
    double bin_hd = bin_hc+1;

    double lev_la = lev_l * bin_ld;
    double lev_ha = lev_h * bin_hd;

    double lev_lt = lev_-lev_l;
    double lev_ht = lev_-lev_h;

    cout << bin-1 << " bin_la " << bin_la << "  bin_lb " <<bin_lb<< "  bin_lc " <<bin_lc
         << "  bin_ld " <<bin_ld
         << "    lev_l "<<lev_l << "  | lev_la " << lev_la
         << "  |  lev_lt " <<lev_lt         <<endl;
    cout << bin+1 << " bin_ha " << bin_ha << "  bin_hb " <<bin_hb<< "  bin_hc " <<bin_hc
         << "  bin_hd " <<bin_hd
         << "    lev_h "<<lev_h << "  | lev_ha " << lev_ha
         << "   | lev_ht " <<lev_ht         <<endl;

    double diff = lev_lt - lev_ht;
    double r = 0;   // used so r could be used in (if else) code

    if(lev_lt < lev_ht){
        double diff = lev_lt - lev_ht;
        r = diff / lev_ht;
    }else{
        r = diff / lev_lt;
    }
    double rh = r/2;
    double move = rh * bin_size;
    double freq = bin_freq + move;
    double p_diff = ((freq/temp_freq)-1)* 100;
    cout << "  diff = "<< diff <<"   r = "<< r << "   r/2 "<<rh <<
        "   move " << move<<endl<<
        "   freq in = "<<temp_freq<<"      freq got = "<< freq <<"      % diff = "<<p_diff<<" % "<<endl<<endl;
}
