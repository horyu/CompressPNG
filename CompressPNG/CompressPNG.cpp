#include "stdafx.h"

using namespace std;
using namespace cv;

// dir_path下の全pngファイルをフルパスでfilesに追加
void get_files(const string& dir_path, vector<string>& files)
{
	// https://qiita.com/episteme/items/0e3c2ee8a8c03780f01e
	// sys = std::tr2::sys; を以下に書き換え
	namespace fs = std::filesystem;
	const fs::path p(dir_path);	// 列挙の起点
	std::for_each(fs::recursive_directory_iterator(p), fs::recursive_directory_iterator(),
		[&files](const fs::path& p) {
			if (fs::is_regular_file(p) && p.extension() == ".png") {
				files.push_back(p.string());
			}
		}
	);
}

int main(int argc, char* argv[])
{
	const clock_t start = clock();
	vector<string> files;

	// これに #pragma omp parallel for を付けると　大量のフォルダ入力で死ぬ
	// これを並列化させても処理時間は全く変わらない
	for (int i = 1; i < argc; i++) {
		//cout << argv[i] << endl;
		get_files(argv[i], files);
	}

	const int size = files.size();
	const vector<int> params{ IMWRITE_PNG_COMPRESSION , 9 };
#pragma omp parallel for schedule(guided)
	for (int i = 0; i < size; i++) {
		const string f = files[i];
		cout << f + "\n" << flush;
		const Mat image = imread(f, 1);		// 読み込み
		imwrite(f, image, params);	// 上書き
	}

	const clock_t end = clock();
	const double time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "ファイル数 : " << size << endl;
	cout << "処理時間   : " << time << endl;
	cout << "[files/s]  : " << size / time << endl;
	cout << "[s/files]  : " << time / size << endl;
	system("pause");

	return 0;
}

