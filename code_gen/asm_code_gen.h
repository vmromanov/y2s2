#pragma once
#include "sintaxer.h"

class asm_code_gen : public Syntax_analyzer
{
	ofstream out;
	const char* filename;
	

public:
	asm_code_gen(const char* file_name) :out("programm.asm"), filename(file_name)
	{

		if (!out.is_open())
		{
			cout << "Ошибка открытия файла записи" << endl;
			system("pause");
			exit;
		}
	}

	void code_gen() {
		this->Syntax_analyzer::start(filename);

		out << "include \\masm32\\include\\masm32rt.inc" << endl << endl << ".386" << endl << endl;
		
		out << ".data?" << endl;
		for (int i = 0; i < 286; i++)
			if (TO[i])
				out << "x"<<i<<" dd " << '?' << endl;
		for (const auto el : table_atoms)
		{
			if (el.type == 7)
				if (el.attribute2 != -1)
					out << 'x' << el.attribute2 << '\t' << "dd" << '\t' << '?' << endl;
		}


		out << endl<<".data" << endl;
		out << "x0 dd 1" << endl;
		for (int i = 287; i < NTtemp; i++)
			out << "x" << i << " dd " << TO[i] << endl;

		out <<endl<< ".code" << endl;
		out << "start:" << endl;
		for (int i = 0; i < table_atoms.size(); i++)
		{
			switch (table_atoms[i].type)
			{
			case 0:
				out << "print str$(x17),10,13" << endl;
				out << "end start";
				break;
			case 1:
				
				out << "label_" << TS.TL_L_inf(table_atoms[i].attribute1) << ':' << endl;
				break;
			case 2:
				out << "mov eax, " << "x" << table_atoms[i].attribute2 << endl;
				out << "mov x" << table_atoms[i].attribute1 << ", eax\n";
				break;
			case 3:
				out << "jmp " << "label_" << (TS.TL_L_inf(table_atoms[i].attribute1)==-1?table_atoms[i].attribute1: TS.TL_L_inf(table_atoms[i].attribute1)) << endl;
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
					out << "mov eax," << 'x' << table_atoms[i].attribute1 << endl;
					out << "cmp eax," << 'x' << table_atoms[i].attribute2 << endl;
				case 1:
					out << "je " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 2:
					
					out << "jl " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 3:
					
					out << "jg " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 4:
					
					out << "jle " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 5:
					
					out << "jge " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				case 6:
				
					out << "jne " << "label_" << TS.TL_L_inf(table_atoms[i].attribute4) << endl;
				}
				break;
			case 7:
				out << "mov eax, " << 'x' << table_atoms[i].attribute1 << endl;
				out << "mov x" << table_atoms[i].attribute2 << " " << ", eax" << endl;
				break;
			case 8:
				out << "label_" << table_atoms[i].attribute1 << ':' << endl;
				break;
			case 9:
				out << "mov eax, " << 'x' << table_atoms[i].attribute1 << endl;
				out << "cmp eax, x" << table_atoms[i].attribute2 << endl;
				out << "jg label_" << table_atoms[i].attribute4 << endl;
				break;
			case 10:
				out << "mov " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "add " << "eax, " << "x" << table_atoms[i].attribute2 << endl;
				out << "mov " << "x" << table_atoms[i].attribute1 << ", eax" << endl;
				break;
			case 11:
				out << "mov " << "eax, " << "x" << table_atoms[i].attribute2 << endl;
				out << "add " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "mov " << "x" << table_atoms[i].attribute3 << ", eax" << endl;
				break;
			case 12:
				out << "mov " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "sub " << "eax, " << "x" << table_atoms[i].attribute2 << endl;
				out << "mov " << "x" << table_atoms[i].attribute3 << ", eax" << endl;
				break;
			case 13:
				out << "mov " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "imul " << "x" << table_atoms[i].attribute2 << endl;
				out << "mov " << "x" << table_atoms[i].attribute3 << ", eax" << endl;
				break;
			case 14:
				out << "mov " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "cdq" << endl;
				out << "idiv x" << table_atoms[i].attribute2 << endl;
				out << "mov " << "x" << table_atoms[i].attribute3 << ", eax" << endl;
				break;
			case 15:
				out << "mov edx, 0" << endl;
				out << "mov eax, x" << table_atoms[i].attribute1 << endl;
				out << "mov ecx, x" << table_atoms[i].attribute2 << endl;
				out << "dec ecx" << endl;
				out << "beg: " << endl;
				out << "mul x" << table_atoms[i].attribute1 << endl;
				out << "loop beg" << endl;
				out << "mov x" << table_atoms[i].attribute3 << ", eax" << endl;
				break;
			case 16:
				out << "mov eax, x" << table_atoms[i].attribute1 << endl;
				out << "mov x" << table_atoms[i].attribute2 << ", eax" << endl;
				break;
			case 17:
				out << "mov " << "eax, " << 0 << endl;
				out << "sub " << "eax, " << "x" << table_atoms[i].attribute1 << endl;
				out << "mov " << "x" << table_atoms[i].attribute2 << ", eax" << endl;
				break;
			
			}
		}
	}



};



