#include <systemc.h>
#include "fir_sc.h"
#include "tb.h"

SC_MODULE(SYSTEM)
{
	tb *tb_0;
	fir_sc *fir_0;
	sc_signal<sc_int<16> > in_sig;
	sc_signal<bool> in_valid_sig;
	sc_signal<bool> in_ready_sig;

	sc_signal<sc_int<16> > out_sig;
	sc_signal<bool> out_valid_sig;
	sc_signal<bool> out_ready_sig;
	sc_signal<bool> reset_sig;
	sc_clock clk_sig;

	SC_CTOR(SYSTEM) : clk_sig("clk_sig",100, SC_NS)
	{
		tb_0 = new tb("tb_0");
		tb_0->clk(clk_sig);
		tb_0->reset(reset_sig);
		tb_0->in(in_sig);
		tb_0->out(out_sig);
		tb_0->in_valid(in_valid_sig);
		tb_0->in_ready(in_ready_sig);
		tb_0->out_valid(out_valid_sig);
		tb_0->out_ready(out_ready_sig);

		fir_0 = new fir_sc("fir_0");
		fir_0->clk(clk_sig);
		fir_0->reset(reset_sig);
		fir_0->data_in(in_sig);
		fir_0->data_out(out_sig);
		fir_0->data_in_valid(in_valid_sig);
		fir_0->data_in_ready(in_ready_sig);
		fir_0->data_out_valid(out_valid_sig);
		fir_0->data_out_ready(out_ready_sig);
	}
	~SYSTEM()
	{
		delete tb_0;
		delete fir_0;
	}
};
SYSTEM *top = NULL;
int main()
{
	top = new SYSTEM("top");
	sc_start();
	return 0;
}
