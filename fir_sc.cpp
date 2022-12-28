#include "fir_sc.h"

void fir_sc::fir_main()
{
	sc_int<16> taps[5];
	#pragma HLS ARRAY_PARTITION variable=taps complete


	//reset
	for(int i=0;i<5;i++)
		taps[i]=0;
	//initialize handshake
	data_in_ready.write(0);
	data_out_valid.write(0);
	data_out.write(0);
	wait();
	while(true)
	{
		sc_int<16> data_in_val;
		sc_int<16> data_out_val;
		//input hand shaking
		///////////////READ INPUT STATE
		data_in_ready.write(1);
		do{
			wait();
		} while (!data_in_valid.read());
		///////////////WRITE OUTPUT STATE

		data_in_val=data_in.read();
		data_in_ready.write(0);

		//taps shift register logic
		for(int i=4;i>0;i--)
		{
			taps[i] = taps[i-1];
		}
		taps[0]=data_in_val;

		// multiply and accumulate
		sc_int<16> val;
		for(int i=0;i<5;i++)
		{
			val+=coef[i]*taps[i];
		}
		//output handshaking
		data_out_valid.write(1);
		data_out.write(val);
		do{
			wait();
		} while(!data_out_ready.read());
		data_out_valid.write(0);
	}
}
