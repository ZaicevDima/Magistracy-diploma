## Настройка Android
В данном разделе приводится пример установки *Android* и запуск эмулятора.

### Скачивание исходников

1. Создание хранилища для системы
```sh
cd ~
mkdir androidx
cd androidx
mkdir bin
```
2. Создание repo-файла и подготовка к скачиванию исходников.
Get a free API Key at [https://example.com](https://example.com)
```sh
curl https://storage.googleapis.com/git-repo-downloads/repo > ./bin/repo
chmod +x ./bin/repo
PATH=~/androidx/bin/:$PATH
mkdir android-source
cd android-source

sed -i '1s/python/python3.6/' ~/androidx/androidsource/bin/repo
```
3. Скачивание нужной версии с [официального сайта Google](https://android.googlesource.com/platform/manifest). В рамках проведенной работы использовался android-11.0.0_r47 
```sh
repo init -u https://android.googlesource.com/platform/manifest -b android-11.0.0_r47
repo sync -j $(grep -c 'processor' /proc/cpuinfo)
```

4. Сборка и запуск эмулятора
```sh
cd ~/androidx/android-source *
source build/envsetup.sh
lunch
aosp_x86-eng
make -j $(grep -c 'processor' /proc/cpuinfo)
emulator
```