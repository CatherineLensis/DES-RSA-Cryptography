#include "MyForm.h"
#include "DES.h"
#include "RSA.h"
#include "Luna.h"
#include "string"
#include <msclr/marshal_cppstd.h>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array <String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	srand((unsigned)time(NULL));
	START::MyForm form;
	Application::Run(% form);
}

System::Void START::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	int n = 0, ee = 0, d = 0;
	if (radioButton1->Checked == true)
	{
		std::string Ключ = Генератор_ключа();
		textBox1->Text = gcnew String(Ключ.c_str());
	}
	if (radioButton2->Checked == true)
	{
		n = System::Convert::ToDouble(textBox2->Text);
		ee = System::Convert::ToDouble(textBox3->Text);
		d = System::Convert::ToDouble(textBox4->Text);
		std::vector<int> key = RSA(n, ee, d);
		std::ostringstream ostr;
		ostr << key[0] << " " << key[1] << " " << key[2];
		std::string Ключ = ostr.str();
		textBox1->Text = gcnew String(Ключ.c_str());

	}


	return System::Void();
}

System::Void START::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	msclr::interop::marshal_context pre;
	String^ Текст = richTextBox1->Text->ToString(); std::string текст = pre.marshal_as<std::string>(Текст);	std::vector <char>  текст_в_байтах(текст.begin(), текст.end());
	if (radioButton1->Checked == true)
	{
	String^ Ключ = textBox1->Text->ToString(); std::string ключ = pre.marshal_as<std::string>(Ключ); std::vector <bool>  ключ_в_битах = Из16в2(ключ);
	
		std::vector <char> текст_в_байтах_кратный_восьмерке = Приведение_к_кратности_восьмерки(текст_в_байтах);
		std::vector <bool> текст_в_битах = bytes2bits(текст_в_байтах_кратный_восьмерке);
		std::vector <std::vector<bool>> текст_в_битах_по_64 = Переход_от_вектора_к_вектору_векторов(текст_в_битах);

		std::vector <bool> Зашифрованный_текст;
		for (int i = 0; i < текст_в_битах_по_64.size(); i++)
		{
			append(Зашифрованный_текст, DES(текст_в_битах_по_64[i], ключ_в_битах, 1));
		}

		std::string B = Из2в16(Зашифрованный_текст);
		richTextBox2->Text = gcnew String(B.c_str());
	}
	if (radioButton2->Checked == true)
	{
		String^ Key = textBox1->Text->ToString(); std::string key = pre.marshal_as<std::string>(Key);
		std::stringstream iss(key);
		int number;
		std::vector<int> K;
		while (iss >> number)
			K.push_back(number);

		std::vector <int> B;
		for (int i = 0; i < текст_в_байтах.size(); i++)
		{
			B.push_back(mod_pow2(текст_в_байтах[i], K[1], K[0]));
		}
		std::stringstream ss;
		for (auto it = B.begin(); it != B.end(); it++) {
			if (it != B.begin())
			{
				ss << " ";
			}
			ss << *it;
		}
		std::string C = ss.str();
		richTextBox2->Text = gcnew String(C.c_str());
	}
	if (radioButton3->Checked == true)
	{

	}
	return System::Void();
}

System::Void START::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	msclr::interop::marshal_context pre;
	String^ Зашифрованый_текст = richTextBox2->Text->ToString(); std::string зашифрованый_текст = pre.marshal_as<std::string>(Зашифрованый_текст);
	if (radioButton1->Checked == true)
	{
		String^ Ключ = textBox1->Text->ToString(); std::string ключ = pre.marshal_as<std::string>(Ключ);   std::vector <bool>  ключ_в_битах = Из16в2(ключ);
		std::vector <bool> Зашифрованный_текст_в_битах = Из16в2(зашифрованый_текст);

		std::vector <bool> Расашифрованный_текст;
		std::vector <std::vector<bool>> текст_в_битах_по_64 = Переход_от_вектора_к_вектору_векторов(Зашифрованный_текст_в_битах);

		for (int i = 0; i < текст_в_битах_по_64.size(); i++)
		{
			append(Расашифрованный_текст, DES(текст_в_битах_по_64[i], ключ_в_битах, 2));
		}

		std::vector <char> A = bits2bytes(Расашифрованный_текст);
		std::string B(A.begin(), A.end());
		richTextBox1->Text = gcnew String(B.c_str());
	}
	if (radioButton2->Checked == true)
	{
		std::stringstream iss(зашифрованый_текст);
		int number;
		std::vector<int> A;
		while (iss >> number)
			A.push_back(number);

		String^ Key = textBox1->Text->ToString(); std::string key = pre.marshal_as<std::string>(Key);
		std::stringstream H(key);
		int M;
		std::vector<int> K;
		while (H >> M)
			K.push_back(M);

		std::vector <char> B;
		for (int i = 0; i < A.size(); i++)
		{
			char sign = mod_pow2(A[i], K[2], K[0]);
			B.push_back(sign);
		}
		std::string C(B.begin(), B.end());
		richTextBox1->Text = gcnew String(C.c_str());
	}

	
	return System::Void();
}

System::Void START::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ OpenFileDialog1 = gcnew OpenFileDialog();

	OpenFileDialog1->Filter = "txt files (*.txt|*.txt|All files (*.*)|*.*";
	OpenFileDialog1->ShowDialog();

	String^ F;
	F = OpenFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	std::string line;

	std::ifstream in(stdF); // окрываем файл для чтения
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл

	textBox1->Text = gcnew String(line.c_str());

	return System::Void();
}

System::Void START::MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ OpenFileDialog1 = gcnew OpenFileDialog();

	OpenFileDialog1->Filter = "txt files (*.txt|*.txt|All files (*.*)|*.*";
	OpenFileDialog1->ShowDialog();

	String^ F;
	F = OpenFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	std::string line;

	std::ifstream in(stdF); // окрываем файл для чтения
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл

	richTextBox1->Text = gcnew String(line.c_str());

	return System::Void();
}

System::Void START::MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ OpenFileDialog1 = gcnew OpenFileDialog();
	OpenFileDialog1->Filter = "txt files (*.txt|*.txt|All files (*.*)|*.*";
	OpenFileDialog1->ShowDialog();

	String^ F;
	F = OpenFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	std::string line;
	std::ifstream in(stdF); // окрываем файл для чтения
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл

	richTextBox2->Text = gcnew String(line.c_str());

	return System::Void();

}

System::Void START::MyForm::button7_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Text file (*.txt)|*.txt";
	saveFileDialog1->ShowDialog();

	String^ F;
	F = saveFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	String^ Key = textBox1->Text->ToString();
	std::string stdKey = pre.marshal_as<std::string>(Key);

	std::ofstream out(stdF);
	out << stdKey;
	out.close();

	return System::Void();
}

System::Void START::MyForm::button8_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Text file (*.txt)|*.txt";
	saveFileDialog1->ShowDialog();

	String^ F;
	F = saveFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	String^ Key = richTextBox1->Text->ToString();
	std::string stdKey = pre.marshal_as<std::string>(Key);

	std::ofstream out(stdF);
	out << stdKey;
	out.close();

	return System::Void();
}

System::Void START::MyForm::button9_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Text file (*.txt)|*.txt";
	saveFileDialog1->ShowDialog();

	String^ F;
	F = saveFileDialog1->FileName;

	msclr::interop::marshal_context pre;
	std::string stdF = pre.marshal_as<std::string>(F);

	String^ Key = richTextBox2->Text->ToString();
	std::string stdKey = pre.marshal_as<std::string>(Key);

	std::ofstream out(stdF);
	out << stdKey;
	out.close();

	return System::Void();
}


 