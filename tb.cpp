#include "tb.h"
void tb::source()
{
	//reset
	in.write(0);
	in_valid.write(0);
	reset.write(1);
	wait();
	reset.write(0);
	wait();
	sc_int<16> tmp;
	for(int i=0;i<64;i++)
	{
		if(i>23 && i<29)
			tmp = 256;
		else
			tmp = 0;
		in_valid.write(1);
		in.write(tmp);
		start_time[i] = sc_time_stamp();

		do{
			wait();
		} while(!in_ready.read());
		in_valid.write(0);
	}
	wait(10000);
	printf("Hanging simulation was stopped by TB source thread.\n");
	sc_stop();
}

void tb::sink()
{
	sc_int<16> out_data;
	//extract clock
	sc_clock *clk_p = DCAST<sc_clock*>(clk.get_interface());
	clk_period = clk_p->period();
	//open simulation output file
	char output_file[256];
	sprintf(output_file,"./output.dat");
	outfp = fopen(output_file,"wb");
	if(outfp == NULL)
	{
		printf("Failed to opne file\n");
		exit(0);
	}
	//initialize port
	out_ready.write(0);
	double total_cycles = 0;
	for(int i=0;i<64;i++)
	{
		out_ready.write(1);
		do{
			wait();
		} while(!out_valid.read());
		out_data = out.read();
		out_ready.write(0);
		end_time[i] = sc_time_stamp();
		double current_latency_cycles = (end_time[i]-start_time[i])/clk_period;
		total_cycles += current_latency_cycles;
		fprintf(outfp, "%d\n", (int)out_data);
		cout<<i <<" :\t"<<out_data.to_double()<<endl;
	}

	//print throughput
	double total_throughput = (start_time[63]-start_time[0])/(clk_period);
	printf("Average throughput is %g cycles.\n",(double)total_throughput/63);

	//print avg latency
	printf("Average latency is %g cycles.\n",(double)total_cycles/64);
	fclose(outfp);
	sc_stop();
}
