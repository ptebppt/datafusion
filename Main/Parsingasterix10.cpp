#include<pch.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include<iostream>
#include <iomanip> //for std::setprecision >> mengatur jumlah desimal di belakang koma
#include <vector>
#include <string>
#include "Parsingasterix10.h"

struct partial_asterix {
	std::vector<std::string> asterix_take;
	std::vector<std::string> asterix_remain;
};

struct data_item {
	std::vector<std::string> i010;
	std::vector<std::string> i000;
	std::vector<std::string> i020;
	std::vector<std::string> i140;
	std::vector<std::string> i041;
	std::vector<std::string> i040;
	std::vector<std::string> i042;
	std::vector<std::string> i200;
	std::vector<std::string> i202;
	std::vector<std::string> i161;
	std::vector<std::string> i170;
	std::vector<std::string> i060;
	std::vector<std::string> i220;
	std::vector<std::string> i245;
	std::vector<std::string> i250;
	std::vector<std::string> i300;
	std::vector<std::string> i090;
	std::vector<std::string> i091;
	std::vector<std::string> i270;
	std::vector<std::string> i550;
	std::vector<std::string> i310;
	std::vector<std::string> i500;
	std::vector<std::string> i280;
	std::vector<std::string> i131;
	std::vector<std::string> i210;
}itemset;

struct record_asterix {
	data_item record[20];
};

std::vector<std::string> Asterix10_parser::Hextobin(std::vector<std::string> results) {
	int jbyte = results.size();
	std::vector<std::string> paketbyte;
	std::string hexo, hexoold, hexocon, bytecon, byteoold, byteo;
	for (int j = 0; j < jbyte; j++) {
		std::string hex = results[j];
		for (int i = 0; i <= 1; i++) {
			switch (hex[i])
			{
			case '0':
				hexo = "0000";
				break;
			case '1':
				hexo = "0001";
				break;
			case '2':
				hexo = "0010";
				break;
			case '3':
				hexo = "0011";
				break;
			case '4':
				hexo = "0100";
				break;
			case '5':
				hexo = "0101";
				break;
			case '6':
				hexo = "0110";
				break;
			case '7':
				hexo = "0111";
				break;
			case '8':
				hexo = "1000";
				break;
			case '9':
				hexo = "1001";
				break;
			case 'a':
			case 'A':
				hexo = "1010";
				break;
			case 'b':
			case 'B':
				hexo = "1011";
				break;
			case 'C':
			case 'c':
				hexo = "1100";
				break;
			case 'd':
			case 'D':
				hexo = "1101";
				break;
			case 'e':
			case 'E':
				hexo = "1110";
				break;
			case 'f':
			case 'F':
				hexo = "1111";
				break;
			}
			hexocon = hexoold + hexo;
			hexoold = hexo;
		}
		paketbyte.push_back(hexocon);
	}
	return paketbyte;
}

std::string vectostring(std::vector<std::string> paket)
{
	std::string paketstring = "";
	int n = paket.size();
	for (int i = 0; i < n; i++)
	{
		paketstring = paketstring + paket[i];
	}
	//std::cout << paketstring << std::endl;
	return paketstring;
}

void Asterix10_parser::divide_vector(struct partial_asterix* asterix, int start, int stop)
{
	std::vector<std::string> vector_take, vector_remain;
	std::vector<std::string> paketbit = asterix->asterix_remain;
	for (int i = start; i <= stop; i++) {
		vector_take.push_back(paketbit[i]);
	}
	for (int i = stop + 1; i < paketbit.size(); i++) {
		vector_remain.push_back(paketbit[i]);
	}
	asterix->asterix_remain = vector_remain;
	asterix->asterix_take = vector_take;
}


std::string Asterix10_parser::Fspec(struct partial_asterix* paketbitv) {
	std::string fspec, fspec1 = "", fspec2 = "", fspec3 = "", fspec4 = "";
	fspec1 = paketbitv->asterix_remain[0];
	if (fspec1[7] == '1') {
		fspec2 = paketbitv->asterix_remain[1];
		if (fspec2[7] == '1') {
			fspec3 = paketbitv->asterix_remain[2];
			if (fspec3[7] == '1') {
				fspec4 = paketbitv->asterix_remain[3];
			}
		}
	}
	fspec = fspec1 + fspec2 + fspec3 + fspec4;
	int fspec_size = fspec.length() / 8;
	divide_vector(paketbitv, 0, fspec_size - 1);
	return fspec;
}

void Asterix10_parser::sequence(std::string tes)
{
	std::string hasil = tes, fspec;
	std::vector<std::string> pakethex, paketbitv, cat, len;
	boost::split(pakethex, hasil, [](char c) {return c == ','; });
	//struct partial_asterix paketvar;
	struct partial_asterix* paket;
	struct record_asterix* record;
	paket = new struct partial_asterix;
	record = new struct record_asterix;
	if (paket == NULL) exit(1);
	//paket = &paketvar;
	paket->asterix_remain = Hextobin(pakethex);
	//vectostring(paket->asterix_remain);
	//std::cout << paket->asterix_remain[0] << std::endl;
	divide_vector(paket, 0, 0);
	cat = paket->asterix_take;
	std::cout << "cat: " << cat[0] << std::endl;
	divide_vector(paket, 0, 1);
	len = paket->asterix_take;
	std::cout << "len: " << std::stoi(len[0] + len[1], nullptr, 2) << std::endl;
	int record_flag = 0, record_number = 0;
	while (record_flag == 0){
		fspec = Fspec(paket);
		std::cout << "FSPEC : " << fspec << std::endl;
		I010(fspec, paket);
		I000(fspec, paket);
		I020(fspec, paket);
		I140(fspec, paket);
		I041(fspec, paket);
		I040(fspec, paket);
		I042(fspec, paket);
		if (fspec[7] == '1')
		{
			I200(fspec, paket);
			I202(fspec, paket);
			I161(fspec, paket);
			I170(fspec, paket);
			I060(fspec, paket);
			I220(fspec, paket);
			I245(fspec, paket);
			if (fspec[15] == '1')
			{
				I250(fspec, paket);
				I300(fspec, paket);
				I090(fspec, paket);
				I091(fspec, paket);
				I270(fspec, paket);
				I550(fspec, paket);
				I310(fspec, paket);

				if (fspec[23] == '1')
				{
					I500(fspec, paket);
					I280(fspec, paket);
					I131(fspec, paket);
					I210(fspec, paket);
				}
			}
		}
		record->record[record_number] = itemset;
		if (paket->asterix_remain[0] == "\0")record_flag = 1;
		else record_flag = 0;
		record_number++;
	}
	free(paket);
}

void Asterix10_parser::I010(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[0] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i010 = paket->asterix_take;
		std::cout << "i010 : ";
		std::cout << vectostring(itemset.i010) << std::endl;
	}
}

void Asterix10_parser::I000(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[1] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i000 = paket->asterix_take;
		std::cout << "i000 : ";
		std::cout << vectostring(itemset.i000) << std::endl;
	}
}

void Asterix10_parser::I020(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[2] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i020 = paket->asterix_take;
		if (itemset.i020[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i020.push_back(paket->asterix_take[0]);
			if (itemset.i020[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i020.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i020 : ";
		std::cout << vectostring(itemset.i020) << std::endl;
	}
}

void Asterix10_parser::I140(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[3] == '1')
	{
		divide_vector(paket, 0, 2);
		itemset.i140 = paket->asterix_take;
		std::cout << "i140 : ";
		std::cout << vectostring(itemset.i140) << std::endl;
	}

}

void Asterix10_parser::I041(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[4] == '1')
	{
		divide_vector(paket, 0, 7);
		itemset.i041 = paket->asterix_take;
		std::cout << "i041 : ";
		std::cout << vectostring(itemset.i041) << std::endl;
	}

}

void Asterix10_parser::I040(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[5] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i040 = paket->asterix_take;
		std::cout << "i040 : ";
		std::cout << vectostring(itemset.i040) << std::endl;
	}
}

void Asterix10_parser::I042(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[6] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i042 = paket->asterix_take;
		std::cout << "i042 : ";
		std::cout << vectostring(itemset.i042) << std::endl;
	}
}

void Asterix10_parser::I200(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[8] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i200 = paket->asterix_take;
		std::cout << "i200 : ";
		vectostring(itemset.i200);
	}
}

void Asterix10_parser::I202(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[9] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i202 = paket->asterix_take;
		std::cout << "i202 : ";
		vectostring(itemset.i202);
	}
}

void Asterix10_parser::I161(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[10] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i161 = paket->asterix_take;
		std::cout << "i161 : ";
		vectostring(itemset.i161);
	}
}

void Asterix10_parser::I170(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[11] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i170 = paket->asterix_take;
		if (itemset.i170[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i170.push_back(paket->asterix_take[0]);
			if (itemset.i170[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i170.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i170 : ";
		vectostring(itemset.i170);
	}
}

void Asterix10_parser::I060(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[12] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i060 = paket->asterix_take;
		std::cout << "i060 : ";
		vectostring(itemset.i060);
	}
}

void Asterix10_parser::I220(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[13] == '1')
	{
		divide_vector(paket, 0, 2);
		itemset.i220 = paket->asterix_take;
		std::cout << "i220 : ";
		vectostring(itemset.i220);
	}
}

void Asterix10_parser::I245(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[14] == '1')
	{
		divide_vector(paket, 0, 6);
		itemset.i245 = paket->asterix_take;
		std::cout << "i245 : ";
		vectostring(itemset.i245);
	}
}

void Asterix10_parser::I250(std::string fspec, struct partial_asterix* paket)
{
	int multiply;
	if (fspec[16] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i250 = paket->asterix_take;
		multiply = stoi(itemset.i250[0]) * 8;
		divide_vector(paket, 0, multiply - 1);
		std::cout << "i250 : ";
		vectostring(itemset.i250);
	}
}

void Asterix10_parser::I300(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[17] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i300 = paket->asterix_take;
		std::cout << "i300 : ";
		vectostring(itemset.i300);
	}
}

void Asterix10_parser::I090(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[18] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i090 = paket->asterix_take;
		std::cout << "i090 : ";
		vectostring(itemset.i090);
	}
}

void Asterix10_parser::I091(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[19] == '1')
	{
		divide_vector(paket, 0, 1);
		std::cout << "i091 : ";
		itemset.i091 = paket->asterix_take;
	}
	vectostring(itemset.i091);
}

void Asterix10_parser::I270(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[20] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i270 = paket->asterix_take;
		if (itemset.i270[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i270.push_back(paket->asterix_take[0]);
			if (itemset.i270[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i270.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i270 : ";
		std::cout << vectostring(itemset.i270) << std::endl;
	}
}


void Asterix10_parser::I550(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[21] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i550 = paket->asterix_take;
		std::cout << "i550 : ";
		vectostring(itemset.i550);
	}

}

void Asterix10_parser::I310(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[22] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i310 = paket->asterix_take;
		std::cout << "i310 : ";
		vectostring(itemset.i310);
	}
}

void Asterix10_parser::I500(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[24] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i500 = paket->asterix_take;
		std::cout << "i500 : ";
		std::cout << vectostring(itemset.i500) << std::endl;
	}
}

void Asterix10_parser::I280(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[25] == '1')
	{
		int multiply;
		divide_vector(paket, 0, 0);
		itemset.i280 = paket->asterix_take;
		multiply = stoi(itemset.i280[0]) * 2;
		divide_vector(paket, 0, (multiply - 1));
		std::cout << "i280 : ";
		vectostring(itemset.i280);
	}
}

void Asterix10_parser::I131(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[26] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i131 = paket->asterix_take;
		std::cout << "i131 : ";
		std::cout << vectostring(itemset.i131) << std::endl;
	}
}

void Asterix10_parser::I210(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[27] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i210 = paket->asterix_take;
		std::cout << "i210 : ";
		vectostring(itemset.i210);
	}
}


//-------------------------------------DECODER PROGRAM--------------------------------------//
//-------------------------------------DECODER PROGRAM--------------------------------------//

std::string Asterix10_decoder::take_sequence(std::string bit_series, int start, int stop) {
	std::string used_bit = "";
	int j = 0;
	for (int i=start;i<=stop;i++){	
		used_bit = used_bit + bit_series[i];
		j++;
	}
	return used_bit;
}

void Asterix10_decoder::I020(struct data_item itemset) {
	std::string item_020 = vectostring(itemset.i020);
	std::string item_020_1, item_020_2, item_020_3, sensor_type, mlat_rply_status, vehicle_type, report_source;
	item_020_1 = take_sequence(item_020, 0, 7);
	int sensor_type_bit = stoi(take_sequence(item_020_1, 5, 7),nullptr,2);
	switch (sensor_type_bit)
	{
	case 0:
		sensor_type = "SSR multilateration";
		break;
	case 1:
		sensor_type = "Mode S multilateration";
		break;
	case 2:
		sensor_type = "ADS-B";
		break;
	case 3:
		sensor_type = "PSR";
		break;
	case 4:
		sensor_type = "Magnetic Loop System";
		break;
	case 5:
		sensor_type = "HF multilateration";
		break;
	case 6:
		sensor_type = "Not defined";
		break;
	case 7:
		sensor_type = "Other types";
		break;
	default:
		break;
	}

	int mlat_rply_status_bit = stoi(take_sequence(item_020_1, 1, 1));
	switch (mlat_rply_status_bit)
	{
	case 1:
		mlat_rply_status = "Corrupted";
		break;
	case 0:
		mlat_rply_status = "Not corrupted";
		break;
	}
	
	if (item_020_1[0] == '1') {
		item_020_2 = take_sequence(item_020, 8, 15);

		int report_source_bit = std::stoi(take_sequence(item_020_2, 5, 5));
		switch (report_source_bit) {
		case 1:
			report_source = "Report from target transponder";
			break;
		case 0:
			report_source = "Report from fixed transponder";
			break;
		}

		int vehicle_type_bit = stoi(take_sequence(item_020_2, 1, 2), nullptr, 2);
		switch (vehicle_type_bit) {
		case 0:
			vehicle_type = "Undetermined";
			break;
		case 1:
			vehicle_type = "Aircraft";
			break;
		case 2:
			vehicle_type = "Ground vehicle";
			break;
		case 3:
			vehicle_type = "Helicopter";
			break;
		}

		if (item_020_2[0] == '1') {
			item_020_3 = take_sequence(item_020, 16, 23);
		}
	}
	std::cout << "Tipe sensor : ";
	std::cout << sensor_type << std::endl;
	std::cout << "Corrupt status : ";
	std::cout << mlat_rply_status << std::endl;
	std::cout << "Transponder source : ";
	std::cout << report_source << std::endl;
	std::cout << "Vehicle type : ";
	std::cout << vehicle_type << std::endl;
}

void Asterix10_decoder::I010(struct data_item itemset) {
	std::string item_010 = vectostring(itemset.i010);
	std::string sic = take_sequence(item_010, 8, 15);
	std::cout << "SAC: " << 0 << std::endl;
	std::cout << "SIC: " << std::stoi(sic, nullptr, 2) << std::endl;
}

void Asterix10_decoder::I140(struct data_item itemset) {
	std::string i140int = vectostring(itemset.i140);
	double mul_timestamp = std::stoi(i140int, nullptr, 2);
	double timestamp = (mul_timestamp * 1) / 128;
	std::cout << "timestamp : ";
	std::cout << std::setprecision(7) << std::fixed;
	std::cout << timestamp << " detik" << std::endl;
}

/*I010/161: Track Number (An integer value representing a unique reference
to a track record within a particular track file)*/
//added by DENA 26/03/2019
void Asterix10_decoder::I161(struct data_item itemset) {
	std::vector<std::string> item_161=itemset.i161;
	int jumlah = item_161.size(); //jumlah data dalam vector item_161
	int track_numb = 0;
	for (int i = 0; i <= jumlah - 1; i++) {
		track_numb = track_numb + std::stoi(item_161[i], nullptr, 2);
	}
	std::cout << "Track Number: ";
	std::cout << track_numb << std::endl;
	}

/*I010/210: Calculated Acceleration (Calculated acceleration of the target,
in two's complement form.)*/
//bits 9 & 1 (LSB) = 0.25 m/s2 (resolution)
//Max.range = +- 31 m/s2
//added by DENA 01/04/2019
void Asterix10_decoder::I210(struct data_item itemset) {
	std::string item_210 = vectostring(itemset.i210);
	std::string item_210_1, item_210_2;
	item_210_1 = take_sequence(item_210, 0, 7);
	item_210_2 = take_sequence(item_210, 8, 15);
	float accx = 0, accy = 0;
	
	//program utk X-axis
	//program jika bit-0 bernilai 0
	if (item_210_1[0] == '0') {
		for (int i = item_210_1.length() - 1; i >= 0; i--) {
			if (item_210[i] == '1') {
				accx = accx + (1 * pow(2, (5 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_210_1[0] == '1') {
		if (std::stoi(item_210_1, nullptr, 2) > 128) {
			for (int i = item_210_1.length() - 1; i > 0; i--) {
				if (item_210_1[i] == '1') {
					accx = accx + (-1 * pow(2, (5 - i)));
				}
			}
		}
		else {
			accx = 32;
		}
	}

	//program utk Y-axis
	//program jika bit-0 bernilai 0
	if (item_210_2[0] == '0') {
		for (int i = item_210_2.length() - 1; i >= 0; i--) {
			if (item_210[i] == '1') {
				accy = accy + (1 * pow(2, (5 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_210_2[0] == '1') {
		if (std::stoi(item_210_2, nullptr, 2) > 128) {
			for (int i = item_210_2.length() - 1; i > 0; i--) {
				if (item_210_2[i] == '1') {
					accy = accy + (-1 * pow(2, (5 - i)));
				}
			}
		}
		else {
			accy = 32;
		}
	}

	std::cout << "Calculated Acceleration X-axis: " << accx << " m/s2" << std::endl;
	std::cout << "Calculated Acceleration Y-axis: " << accy << " m/s2" << std::endl;
}

/*I010/000: Message Type. This data item allows for a more convenient handling of the
messages at the receiver side by further defining the type of transaction*/
//added by DENA 03/04/2019
void Asterix10_decoder::I000(struct data_item itemset) {
	std::string item_000 = vectostring(itemset.i000);
	std::string messtype;
	int messtype_val = std::stoi(item_000, nullptr, 2);
	switch (messtype_val)
	{
	case 1:
		messtype = "Target Report";
		break;
	case 2:
		messtype = "Start of Update Cycle";
		break;
	case 3:
		messtype = "Periodic Status Message";
		break;
	case 4:
		messtype = "Event-triggered Status Message";
		break;
	}
	std::cout << "Message Type: " << messtype << std::endl;
}

//I010/202: Calculated track velocity in cartesian co-ordinates
//bits 17 & 1 (LSB) = 0.25 m/s (resolution)
//Max.range = +- 8192 m/s
//added by DENA 06/04/2019
void Asterix10_decoder::I202(struct data_item itemset) {
	std::string item_202 = vectostring(itemset.i202);
	std::string item_202_1, item_202_2;
	item_202_1 = take_sequence(item_202, 0, 15);
	item_202_2 = take_sequence(item_202, 16, 31);
	float velx = 0, vely = 0;

	//program utk X-axis
	//program jika bit-0 bernilai 0
	if (item_202_1[0] == '0') {
		for (int i = item_202_1.length() - 1; i >= 0; i--) {
			if (item_202_1[i] == '1') {
				velx = velx + (1 * pow(2, (13 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_202_1[0] == '1') {
		if (std::stoi(item_202_1, nullptr, 2) > 32768) {
			for (int i = item_202_1.length() - 1; i > 0; i--) {
				if (item_202_1[i] == '1') {
					velx = velx + (-1 * pow(2, (13 - i)));
				}
			}
		}
		else {
			velx = 8192;
		}
	}

	//program utk Y-axis
	//program jika bit-0 bernilai 0
	if (item_202_2[0] == '0') {
		for (int i = item_202_2.length() - 1; i >= 0; i--) {
			if (item_202_2[i] == '1') {
				vely = vely + (1 * pow(2, (13 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_202_2[0] == '1') {
		if (std::stoi(item_202_2, nullptr, 2) > 32768) {
			for (int i = item_202_2.length() - 1; i > 0; i--) {
				if (item_202_2[i] == '1') {
					vely = vely + (-1 * pow(2, (13 - i)));
				}
			}
		}
		else {
			vely = 8192;
		}
	}

	std::cout << "Calculated Velocity X-axis: " << velx << " m/s" << std::endl;
	std::cout << "Calculated Velocity Y-axis: " << vely << " m/s" << std::endl;
}

/*I010/042: Position in Cartesian Co-ordinates (Position of a target in Cartesian co-ordinates,
in two's complement form.)*/
//bits 17 & 1 (LSB) = 1m (resolution)
//Max.range = +- 32768 m
//added by DENA 06/04/2019
void Asterix10_decoder::I042(struct data_item itemset) {
	std::string item_042 = vectostring(itemset.i042);
	std::string item_042_1, item_042_2;
	item_042_1 = take_sequence(item_042, 0, 15);
	item_042_2 = take_sequence(item_042, 16, 31);
	int posx = 0, posy = 0;

	//program utk X-axis
	//program jika bit-0 bernilai 0
	if (item_042_1[0] == '0') {
		for (int i = item_042_1.length() - 1; i >= 0; i--) {
			if (item_042_1[i] == '1') {
				posx = posx + (1 * pow(2, 15-i));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_042_1[0] == '1') {
		if (std::stoi(item_042_1, nullptr, 2) > 32768) {
			for (int i = item_042_1.length() - 1; i > 0; i--) {
				if (item_042_1[i] == '1') {
					posx = posx + (-1 * pow(2, 15-i));
				}
			}
		}
		else {
			posx = 32768;
		}
	}

	//program utk Y-axis
	//program jika bit-0 bernilai 0
	if (item_042_2[0] == '0') {
		for (int i = item_042_2.length() - 1; i >= 0; i--) {
			if (item_042_2[i] == '1') {
				posy = posy + (1 * pow(2, 15-i));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_042_2[0] == '1') {
		if (std::stoi(item_042_2, nullptr, 2) > 32768) {
			for (int i = item_042_2.length() - 1; i > 0; i--) {
				if (item_042_2[i] == '1') {
					posy = posy + (-1 * pow(2, 15-i));
				}
			}
		}
		else {
			posy = 32768;
		}
	}

	std::cout << "Position of Target X-axis: " << posx << " m" << std::endl;
	std::cout << "Position of Target Y-axis: " << posy << " m" << std::endl;
}

//I010/040: Position of Target in Polar Co-ordinates
//bit 17 (LSB) = 1m (resolution), Max.range = 65536 m
//bit 17-32: r (radius)
//bit 1 (LSB) = 360 degree/(2^16) = 0.0055 degree (resolution)
//bit 1-16: theta (sudut)
//added by DENA 06/04/2019
void Asterix10_decoder::I040(struct data_item itemset) {
	std::string item_040 = vectostring(itemset.i040);
	std::string item_040_1, item_040_2;
	item_040_1 = take_sequence(item_040, 0, 15);
	item_040_2 = take_sequence(item_040, 16, 31);
	int r = 0; float theta = 0;

	//program utk r
	for (int i = item_040_1.length() - 1; i >= 0; i--) {
		if (item_040_1[i] == '1') {
			r = r + (1 * pow(2, 15 - i));
		}
	}

	//program utk theta
	for (int i = item_040_2.length() - 1; i >= 0; i--) {
			if (item_040_2[i] == '1') {
				theta = theta + (1 * pow(2, 7.4918 - i));
			}
	}
	
	std::cout << "Position of Target r: " << r << " m" << std::endl;
	std::cout << std::setprecision(4) << std::fixed; /*atur 4 angka desimal
	di belakang koma utk theta*/
	std::cout << "Position of Target theta: " << theta << " degree" << std::endl;
}

/*I010/091: Measured Height (Height above local 2D co-ordinate reference system
(two's complement) based on direct measurements not related to barometric pressure*/
//bit 1 (LSB) = 6.25 ft (resolution)
//range: +/- 204800 ft
//added by DENA 06/04/2019
void Asterix10_decoder::I091(struct data_item itemset) {
	std::string item_091 = vectostring(itemset.i091);
	float height = 0;
	
	if (item_091[0] == '0') {
		for (int i = item_091.length() - 1; i >= 0; i--) {
			if (item_091[i] == '1') {
				height = height + (1 * pow(2, 17.643856 - i));
			}
		}
	}

	if (item_091[0] == '1') {
		if (std::stoi(item_091, nullptr, 2) > 32768) {
			for (int i = item_091.length() - 1; i > 0; i--) {
				if (item_091[i] == '1') {
					height = height + (-1 * pow(2, 17.643856 - i));
				}
			}
		}
		else {
			height = 204800;
		}
	}
	
	std::cout << std::setprecision(4) << std::fixed; /*atur 4 angka desimal
	di belakang koma*/
	std::cout << "Measured height: " << height << " ft" << std::endl;
}

/*int main() {
	Asterix10_parser ins1;
	Asterix10_decoder ins1d;
	std::string tes = "0a,00,27,ff,01,09,a0,00,04,01,69,00,1c,57,e2,fb,a6,89,7c,4b,d9,9e,98,00,e0,4d,8d,01,53,fc,e6,3d,59,16,17,12,ff,b2,83";
		//"0a,00,27,ff,01,09,a0,00,04,01,61,00,1c,59,46,fb,a7,2c,52,4b,d9,97,9c,01,72,16,75,01,42,fb,64,51,2f,28,20,15,00,60,90";
		//"0a,00,27,ff,01,09,a0,00,04,01,69,00,1c,57,e2,fb,a6,89,7c,4b,d9,9e,98,00,e0,4d,8d,01,53,fc,e6,3d,59,16,17,12,ff,b2,83";
		//"0a,00,14,d0,00,04,02,1c,57,c0,d1,01,04,00,04,03,1c,57,c0,00";
		//"0a,00,27,ff,01,09,a0,00,03,01,61,00,1c,59,4c,fb,a3,f2,82,4b,d8,cd,be,02,1f,36,2c,ff,63,03,0c,63,33,28,2c,17,00,97,8f";	
	ins1.sequence(tes);
	//ins1d.I210(itemset);
	return 0; */

int main() {
	Asterix10_decoder decoder;
	std::vector<std::string> inputvec = { "1000000011111111" };
	std::string item_210 = vectostring(inputvec);
	std::string item_210_1, item_210_2;
	item_210_1 = decoder.take_sequence(item_210, 0, 7);
	item_210_2 = decoder.take_sequence(item_210, 8, 15);
	float accx = 0, accy = 0;

	//program utk X-axis
	//program jika bit-0 bernilai 0
	if (item_210_1[0] == '0') {
		for (int i = item_210_1.length() - 1; i >= 0; i--) {
			if (item_210[i] == '1') {
				accx = accx + (1 * pow(2, (5 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_210_1[0] == '1') {
		if (std::stoi(item_210_1, nullptr, 2) > 128) {
			for (int i = item_210_1.length() - 1; i > 0; i--) {
				if (item_210_1[i] == '1') {
					accx = accx + (-1 * pow(2, (5 - i)));
				}
			}
		}
		else {
			accx = 32;
		}
	}

	//program utk Y-axis
	//program jika bit-0 bernilai 0
	if (item_210_2[0] == '0') {
		for (int i = item_210_2.length() - 1; i >= 0; i--) {
			if (item_210[i] == '1') {
				accy = accy + (1 * pow(2, (5 - i)));
			}
		}
	}
	//program jika bit-0 bernilai 1
	if (item_210_2[0] == '1') {
		if (std::stoi(item_210_2, nullptr, 2) > 128) {
			for (int i = item_210_2.length() - 1; i > 0; i--) {
				if (item_210_2[i] == '1') {
					accy = accy + (-1 * pow(2, (5 - i)));
				}
			}
		}
		else {
			accy = 32;
		}
	}

	std::cout << "Calculated Acceleration X-axis: " << accx << " m/s2" << std::endl;
	std::cout << "Calculated Acceleration Y-axis: " << accy << " m/s2" << std::endl;
}