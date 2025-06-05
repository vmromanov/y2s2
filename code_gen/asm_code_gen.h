#pragma once
#include "sintaxer.h"

class asm_code_gen : public Syntax_analyzer
{
	ofstream out;

	asm_code_gen(string file_name):out(file_name)
	{}

public:
	void code_gen() {



		out << "include \\masm32\\include\\masm32rt.inc" << endl << endl << ".365" << endl << endl;
		
		out << ".data?" << endl;
		for (int i = 0; i < 286; i++)
			if (TO[i] == 1)
				out << (char)(i + 'A') << '\t' << "dd" << '\t' << '?' << endl;


		for (int i = 0; i < table_atoms.size(); i++)
		{
			switch (table_atoms[i].type)
			{
			case 0:
				out << "end start";
				break;
			case 1:
				out << "label_" << TS.TL_L_inf(table_atoms[i].attribute1) << ':' << endl;
				break;
			case 3:
				out << "jmp " << "label_" << TS.TL_L_inf(table_atoms[i].attribute1) << endl;
				break;
			case 4:
				out << "call label_" << TS.TL_L_inf(table_atoms[i].attribute1) << endl;
				break;
			case 5:
				out << "ret" << endl;
				break;
			case 6:
				switch (table_atoms[i].attribute3)
				{
				case 1:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "je " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 2:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "jl " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 3:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "jg " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 4:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "jle " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 5:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "jge " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 6:
					out << "mov eax," << (char)(table_atoms[i].attribute1 + 'A') << endl;
					out << "cmp eax," << (char)(table_atoms[i].attribute2 + 'A') << endl;
					out << "jne " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				}
				break;
			case 7:

				break;
			case 8:

				break;
			case 9:

				break;
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			case 15:

				break;
			case 16:

				break;
			case 17:

				break;
			case 18:

				break;
			}
		}
	}



};



