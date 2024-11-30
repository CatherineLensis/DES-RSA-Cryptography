#include <vector>
#include "string"
#include <unordered_map>

std::vector<char> bits2bytes(const std::vector<bool>& bits)
{
	// Буфер для записи результата.
	size_t byte_num = bits.size() / 8;
	if (bits.size() % 8 > 0) byte_num++;
	// Буфер для записи результата. По умолчанию значения всех бит устанавливаются в FALSE.
	std::vector<char> bytes(byte_num, 0x00);
	// Цикл по байтам данных.
	for (int i = 0; i < bits.size(); i++) {
		// Индекс текущего байта.
		int byte_idx = i / 8;
		// Индекс текущего бита в байте.
		int bit_idx = i % 8;
		// Если текущий бит равен TRUE, то его надо выставить в TRUE. 
		if (bits[i]) bytes[byte_idx] |= (0x01 << (7 - bit_idx));
	}
	return bytes;
}
std::vector<bool> bytes2bits(const std::vector<char>& bytes)
{
	// Буфер для записи результата.
	std::vector<bool> bits(bytes.size() * 8);
	// Цикл по байтам данных.
	for (int byte_idx = 0; byte_idx < bytes.size(); byte_idx++) {
		// Цикл по битам текущего байта.
		for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
			// Установка текущего бита.
			bits[byte_idx * 8 + bit_idx] = ((bytes[byte_idx] >> (7 - bit_idx)) & 0x01);
		}
	}
	return bits;
}
void append(std::vector<bool>& body, const std::vector<bool>& tale)
{
	body.insert(body.end(), tale.begin(), tale.end());
}
void append(std::vector<bool>& body, char tale)
{
	// Цикл по битам в добавляемым байте.
	for (int bit_idx = 0; bit_idx < 8; bit_idx++)
	{
		// Добавление текущего бита.
		body.emplace_back((tale >> (7 - bit_idx)) & 0x01);
	}
}
std::vector<bool> Из16в2(std::string Текст)
{
	std::vector<bool> result;
	std::unordered_map< char, std::vector <bool>> Table
	{
			{ '0', { 0,0,0,0 } }, { '1' , {0,0,0,1}}, { '2', {0,0,1,0}}, { '3', {0,0,1,1}}
			, { '4', {0,1,0,0} }, { '5', {0,1,0,1} }, { '6', {0,1,1,0} }, { '7', {0,1,1,1} }
			, { '8', {1,0,0,0} }, { '9', {1,0,0,1} }, { 'A', {1,0,1,0} }, { 'B', {1,0,1,1} }
			, { 'C',{1,1,0,0} }, { 'D', {1,1,0,1} }, { 'E', {1,1,1,0} }, { 'F', {1,1,1,1} }
	};
	for (int i = 0; i < Текст.size(); i++)
	{
		append(result, Table[Текст[i]]);
	}
	return result;
}
std::string Из2в16(std::vector<bool> Текст)
{
	std::string result;
	std::unordered_map< std::vector <bool>, char> Table
	{
				{ {0,0,0,0}, '0'}, {{0,0,0,1}, '1' }, {{0,0,1,0}, '2' }, {{0,0,1,1}, '3' }
			,	{ {0,1,0,0}, '4'}, {{0,1,0,1}, '5' }, {{0,1,1,0}, '6' }, {{0,1,1,1}, '7' }
			,	{ {1,0,0,0}, '8'}, {{1,0,0,1}, '9' }, {{1,0,1,0}, 'A' }, {{1,0,1,1}, 'B' }
			,	{ {1,1,0,0}, 'C'}, {{1,1,0,1}, 'D' }, {{1,1,1,0}, 'E' }, {{1,1,1,1}, 'F' }
	};
	std::vector<bool> символ; символ.resize(4);
	for (int i = 0; i < Текст.size() / 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			символ[j] = Текст[i * 4 + j];
		}
		result.push_back(Table[символ]);
	}
	return result;
}


bool Случайный_бит()
{
	int бит = rand()%2;
	if (бит == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
std::string Генератор_ключа()
{
	std::string ключ_в_16;
	std::vector<bool> буква_в_бит;
	std::vector<bool> ключ_в_битах;
	буква_в_бит.resize(8);
	for (int i = 0; i < 8; i++)
	{
		int n = 0;
		for (int j = 0; j < 7; j++)
		{
			буква_в_бит[j] = Случайный_бит();
			n += буква_в_бит[j];
		}
		буква_в_бит[7] = (n + 1) % 2;
		append(ключ_в_битах, буква_в_бит);
	}
	ключ_в_16 = Из2в16(ключ_в_битах);
	return  ключ_в_16;
}
std::vector<char> Приведение_к_кратности_восьмерки(std::vector<char> Текст)
{
	std::vector<char> текст = Текст;
	int n = Текст.size();
	if (Текст.size() % 8 != 0)
	{
		n = Текст.size() % 8;
	}
	for (int i = 0; i < 8 - n; i++)
	{
		текст.push_back(' ');
	}
	return текст;
}
std::vector<std::vector <bool>> Переход_от_вектора_к_вектору_векторов(std::vector <bool> Текст)
{
	std::vector<std::vector <bool>> блоки; блоки.resize(Текст.size() / 64);
	std::vector <bool> Слово; Слово.resize(64); 
	for (int Индекс_блока = 0; Индекс_блока < Текст.size()/64; Индекс_блока++)
	{
		for (int Индекс_байта = 0; Индекс_байта < 64; Индекс_байта++)
		{
			Слово[Индекс_байта] = Текст[Индекс_блока * 64 + Индекс_байта];
		}
		блоки[Индекс_блока] = Слово;
	}
	return блоки;
}

