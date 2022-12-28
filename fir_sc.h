#include <systemc.h>

const sc_uint<8> coef[5]={
		18,77,107,77,18
};
SC_MODULE(fir_sc)
{
	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_in<sc_int<16> > data_in;
	sc_out<sc_int<16> > data_out;

	sc_in<bool> data_in_valid;
	sc_out<bool> data_in_ready;
	sc_out<bool> data_out_valid;
	sc_in<bool> data_out_ready;

	void fir_main();
	SC_CTOR(fir_sc)
	{
		SC_CTHREAD(fir_main, clk.pos());
		reset_signal_is(reset,true);
	}
};
