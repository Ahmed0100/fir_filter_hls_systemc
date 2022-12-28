#include <systemc.h>
SC_MODULE(tb)
{
	sc_in<bool> clk;
	sc_out<bool> reset;
	sc_in<sc_int<16> > out;
	sc_out<sc_int<16> > in;
	sc_out<bool> in_valid;
	sc_in<bool> in_ready;
	sc_in<bool> out_valid;
	sc_out<bool> out_ready;
	
	void source();
	void sink();

	FILE* outfp;
	sc_time start_time[64],end_time[64], clk_period;

	SC_CTOR(tb)
	{
		SC_CTHREAD(source,clk.pos());
		SC_CTHREAD(sink,clk.pos());
	}
};
