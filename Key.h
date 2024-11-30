#include <vector>
std::vector <bool> Функция_сжатия(std::vector <bool> K)
{
	std::vector <bool> E;
	E.resize(48);
	std::vector <int> Table
	{
			14, 17, 11, 24, 1, 5
			, 3, 28, 15, 6, 21, 10
			, 23, 19, 12, 4, 26, 8
			, 16, 7, 27, 20, 13, 2
			, 41, 52, 31, 37, 47, 55
			, 30, 40, 51, 45, 33, 48
			, 44, 49, 39, 56, 34, 53
			, 46, 42, 50, 36, 29, 32
	};
	for (int i = 0; i < 48; i++)
	{
		E[i] = K[Table[i] - 1];
	}
	return E;
}
std::vector <bool> Слияние(std::vector<std::vector <bool>> LR)
{
	int N = LR[0].size();
	std::vector <bool> Текст;
	Текст.resize(N * 2);
	for (int i = 0; i < N; i++)
	{
		Текст[i] = LR[0][i];
		Текст[i + N] = LR[1][i];
	}
	return Текст;
}
std::vector <bool> Циклический_сдвиг(std::vector <bool> CD, int n)
{
	std::vector <bool> result = CD;
	for (int i = 0; i < n; i++)
	{
		bool буфер;
		буфер = result[0];
		for (int j = 1; j < 28; j++)
		{
			result[j - 1] = result[j];
		}
		result[27] = буфер;
	}
	result = result;
	return result;
}
std::vector<std::vector <bool>> Индуктивное_преобразование (std::vector<std::vector <bool>> cd)
{
	std::vector<std::vector <bool>> K;  K.resize(16); for (int i = 0; i < 16; i++) { K[i].resize(48); }
	std::vector <int> Table2 {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	for (int i = 0; i < 16; i++)
	{
		cd[0] = Циклический_сдвиг(cd[0], Table2[i]);
		cd[1] = Циклический_сдвиг(cd[1], Table2[i]);
		K[i] = Функция_сжатия(Слияние(cd));
	}
	return K;
}
std::vector <std::vector<bool>> CD(std::vector <bool> ключ)
{
	std::vector <int> Table0
	{	57, 49, 41, 33, 25, 17, 9
		, 1, 58, 50, 42, 34, 26, 18
		, 10, 2, 59, 51, 43, 35, 27
		, 19, 11, 3, 60, 52, 44, 36
		, 63, 55, 47, 39, 31, 23, 15
		, 7, 62, 54, 46, 38, 30, 22
		, 14, 6, 61, 53, 45, 37, 29
		, 21, 13, 5, 28, 20, 12, 4 };

	std::vector <std::vector<bool>> cd; cd.resize(2); cd[0].resize(28); cd[1].resize(28);
	for (int i = 0; i < 28; i++)
	{
		cd[0][i] = ключ[Table0[i] - 1];
	}
	for (int i = 28; i < 56; i++)
	{
		cd[1][i - 28] = ключ[Table0[i] - 1];
	}
	return cd;
}
std::vector<std::vector <bool>> Раундовые_крючи(std::vector <bool> ключ)
{
	std::vector <std::vector<bool>> cd = CD(ключ);
	std::vector<std::vector <bool>> K = Индуктивное_преобразование(cd);
	return K;
}