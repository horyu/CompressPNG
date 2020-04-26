# CompressPNG

入力されたフォルダ直下のPNGファイルをOpenCVを用いて最高圧縮率で並列圧縮します。

## 使用方法

### エクスプローラー

CompressPNG.exe にフォルダ（複数可）をドラッグアンドドロップ。

### コマンドプロンプト・パワーシェル


```
> CompressPNG.exe folder1 folder2
```

## 環境

- Windows 10 Pro
- Microsoft Visual Community 2019
- OpenCV 4.3.0（コンパイルしたのではなくバイナリ）

## メモ

- 圧縮率
  - `IMWRITE_PNG_COMPRESSION` を最大である 9 にしています。
- 並列
  - `#pragma omp parallel for` を用いています。
- [【OpenCV】コンピュータにopencv_objdetect220d.dllがないため、 | イメージングソリューション](https://imagingsolution.net/program/opencv/no-opencv-dll-file/)

