#include "../include/crypto_system.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <ctime>
#include <random>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
namespace fs = std::filesystem;

void CryptoSystem::showMenu() {
    clearScreen();
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║          🔐 КРИПТОГРАФИЧЕСКАЯ СИСТЕМА ЗАЩИТЫ ДАННЫХ 🔐       ║" << endl;
    cout << "║                  (Davydov Maxim AB-421 - 2025)               ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. Ввести текст в файл                                      ║" << endl;
    cout << "║  2. Зашифровать файл                                         ║" << endl;
    cout << "║  3. Расшифровать файл                                        ║" << endl;
    cout << "║  4. Просмотреть содержимое файла                             ║" << endl;
    cout << "║  5. Создать тестовые мультимедиа файлы                       ║" << endl;
    cout << "║  0. Выход                                                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "🎯 Выберите опцию (0-5): ";
}

void CryptoSystem::inputTextToFile() {
    clearScreen();
    cout << "📝 ВВОД ТЕКСТА В ФАЙЛ\n" << endl;
    
    string filename = getFilename("📁 Введите имя файла для сохранения: ");
    
    cout << "\n✍️  Введите текст (для завершения введите '###' на новой строке):" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    string text, line;
    while (getline(cin, line)) {
        if (line == "###") break;
        text += line + "\n";
    }
    
    if (!text.empty() && text.back() == '\n') {
        text.pop_back();
    }
    
    ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        cout << "\n✅ Текст успешно сохранен в файл: " << filename << endl;
        showFileInfo(filename);
    } else {
        cout << "\n❌ Ошибка создания файла!" << endl;
    }
    
    cout << "\n📄 Нажмите Enter для продолжения...";
    cin.get();
}

void CryptoSystem::encryptFile() {
    clearScreen();
    cout << "🔒 ШИФРОВАНИЕ ФАЙЛА\n" << endl;
    
    string filename = chooseFileFromDirectory("📁 Выберите файл для шифрования: ");
    if (filename.empty()) return;
    
    showFileInfo(filename);
    
    int algorithm = chooseAlgorithm();
    string password = getPassword();
    
    vector<unsigned char> data = readBinaryFile(filename);
    if (data.empty()) {
        cout << "❌ Ошибка чтения файла!" << endl;
        return;
    }
    
    cout << "\n🔐 Начинаем шифрование с помощью: ";
    
    switch (algorithm) {
        case RC4:
            cout << "RC4 (поточный шифр)" << endl;
            rc4Encrypt(data, password);
            break;
        case AES_CFB:
            cout << "AES-128 CFB (промышленный стандарт)" << endl;
            aesCfbEncrypt(data, password);
            break;
        case BINARY_VIGENERE:
            cout << "Бинарный Виженер (блочный шифр)" << endl;
            binaryVigenereEncrypt(data, password);
            break;
    }
    
    string encryptedFilename = filename + ".encrypted";
    writeBinaryFile(encryptedFilename, data);
    
    cout << "\n🎉 Файл успешно зашифрован!" << endl;
    cout << "📁 Зашифрованный файл: " << encryptedFilename << endl;
    showFileInfo(encryptedFilename);
    
    cout << "\n📄 Нажмите Enter для продолжения...";
    cin.get();
}

void CryptoSystem::decryptFile() {
    clearScreen();
    cout << "🔓 РАСШИФРОВКА ФАЙЛА\n" << endl;
    
    string filename = chooseFileFromDirectory("📁 Выберите зашифрованный файл: ");
    if (filename.empty()) return;
    
    showFileInfo(filename);
    
    int algorithm = chooseAlgorithm();
    string password = getPassword();
    
    vector<unsigned char> data = readBinaryFile(filename);
    if (data.empty()) {
        cout << "❌ Ошибка чтения файла!" << endl;
        return;
    }
    
    cout << "\n🔓 Начинаем расшифровку с помощью: ";
    
    switch (algorithm) {
        case RC4:
            cout << "RC4 (поточный шифр)" << endl;
            rc4Decrypt(data, password);
            break;
        case AES_CFB:
            cout << "AES-128 CFB (промышленный стандарт)" << endl;
            aesCfbDecrypt(data, password);
            break;
        case BINARY_VIGENERE:
            cout << "Бинарный Виженер (блочный шифр)" << endl;
            binaryVigenereDecrypt(data, password);
            break;
    }
    
    string decryptedFilename;
    if (filename.length() >= 10 && filename.substr(filename.length() - 10) == ".encrypted") {
        decryptedFilename = filename.substr(0, filename.length() - 10) + "_decrypted";
    } else {
        decryptedFilename = filename + "_decrypted";
    }
    
    writeBinaryFile(decryptedFilename, data);
    
    cout << "\n🎉 Файл успешно расшифрован!" << endl;
    cout << "📁 Расшифрованный файл: " << decryptedFilename << endl;
    showFileInfo(decryptedFilename);
    
    cout << "\n📄 Нажмите Enter для продолжения...";
    cin.get();
}

void CryptoSystem::displayFile() {
    clearScreen();
    cout << "👁️  ПРОСМОТР СОДЕРЖИМОГО ФАЙЛА\n" << endl;
    
    string filename = chooseFileFromDirectory("📁 Выберите файл для просмотра: ");
    if (filename.empty()) return;
    
    showFileInfo(filename);
    
    if (isTextFile(filename)) {
        ifstream file(filename);
        if (file.is_open()) {
            cout << "\n📄 СОДЕРЖИМОЕ ФАЙЛА:" << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
            
            string line;
            int lineNum = 1;
            while (getline(file, line)) {
                cout << setw(3) << lineNum++ << " │ " << line << endl;
            }
            file.close();
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        } else {
            cout << "❌ Ошибка открытия файла!" << endl;
        }
    } else {
        cout << "\n🔍 HEX-ДАМП ФАЙЛА (первые 256 байт):" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        vector<unsigned char> data = readBinaryFile(filename);
        int displaySize = min(256, (int)data.size());
        
        for (int i = 0; i < displaySize; i += 16) {
            cout << setfill('0') << setw(4) << hex << i << " │ ";
            
            for (int j = 0; j < 16 && i + j < displaySize; j++) {
                cout << setfill('0') << setw(2) << hex << (int)data[i + j] << " ";
            }
            
            for (int j = displaySize - i; j < 16; j++) {
                cout << "   ";
            }
            
            cout << "│ ";
            for (int j = 0; j < 16 && i + j < displaySize; j++) {
                char c = data[i + j];
                cout << (isprint(c) ? c : '.');
            }
            cout << endl;
        }
        cout << dec << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    }
    
    cout << "\n📄 Нажмите Enter для продолжения...";
    cin.get();
}

void CryptoSystem::createTestFiles() {
    clearScreen();
    cout << "🎬 СОЗДАНИЕ ТЕСТОВЫХ ФАЙЛОВ\n" << endl;
    
    cout << "Выберите тип тестового файла:" << endl;
    cout << "1. 📊 Большой текстовый файл (1MB)" << endl;
    cout << "2. 🖼️  Тестовое изображение BMP" << endl;
    cout << "3. 🎵 Тестовый аудио файл WAV" << endl;
    cout << "4. 🎥 Тестовый видео файл AVI" << endl;
    cout << "5. 📦 Создать все файлы" << endl;
    cout << "Ваш выбор (1-5): ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: createLargeTextFile(); break;
        case 2: createTestImage(); break;
        case 3: createTestAudio(); break;
        case 4: createTestVideo(); break;
        case 5:
            createLargeTextFile();
            createTestImage();
            createTestAudio();
            createTestVideo();
            break;
        default:
            cout << "⚠️  Неверный выбор!" << endl;
            break;
    }
    
    cout << "\n📄 Нажмите Enter для продолжения...";
    cin.get();
}

// Низкоуровневые алгоритмы
void CryptoSystem::rc4Encrypt(vector<unsigned char>& data, const string& key) {
    RC4::encrypt(data, key);
}

void CryptoSystem::rc4Decrypt(vector<unsigned char>& data, const string& key) {
    RC4::decrypt(data, key);
}

void CryptoSystem::aesCfbEncrypt(vector<unsigned char>& data, const string& key) {
    AES_CFB::encrypt(data, key);
}

void CryptoSystem::aesCfbDecrypt(vector<unsigned char>& data, const string& key) {
    AES_CFB::decrypt(data, key);
}

void CryptoSystem::binaryVigenereEncrypt(vector<unsigned char>& data, const string& key) {
    BinaryVigenere::encrypt(data, key);
}

void CryptoSystem::binaryVigenereDecrypt(vector<unsigned char>& data, const string& key) {
    BinaryVigenere::decrypt(data, key);
}

vector<unsigned char> CryptoSystem::readBinaryFile(const string& filename) {
    vector<unsigned char> data;
    ifstream file(filename, ios::binary);
    
    if (file.is_open()) {
        file.seekg(0, ios::end);
        size_t size = file.tellg();
        file.seekg(0, ios::beg);
        
        data.resize(size);
        file.read(reinterpret_cast<char*>(data.data()), size);
        file.close();
    }
    
    return data;
}

void CryptoSystem::writeBinaryFile(const string& filename, const vector<unsigned char>& data) {
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        file.close();
    }
}

string CryptoSystem::getPassword() {
    string password;
    cout << "\n🔑 Введите пароль для шифрования: ";
    getline(cin, password);
    
    if (password.empty()) {
        cout << "⚠️  Пустой пароль! Используется пароль по умолчанию." << endl;
        password = "Kenpach1Zaracki_DefaultKey_2025";
    }
    
    return password;
}

string CryptoSystem::getFilename() {
    string filename;
    cout << "📁 Введите имя файла: ";
    getline(cin, filename);
    return filename;
}

string CryptoSystem::getFilename(const string& prompt) {
    string filename;
    cout << prompt;
    getline(cin, filename);
    return filename;
}

string CryptoSystem::chooseFileFromDirectory(const string& prompt) {
    cout << prompt << endl;
    cout << "\n📂 ДОСТУПНЫЕ ФАЙЛЫ:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    vector<string> files;
    int index = 1;
    
    try {
        // Показываем основные файлы из корня (только важные)
        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.is_regular_file()) {
                string filename = entry.path().filename().string();
                // Исключаем системные файлы
                if (filename != "crypto_app" && filename != "Makefile" && 
                    filename != "README.md" && filename.find(".o") == string::npos &&
                    filename.find(".backup") == string::npos) {
                    files.push_back(filename);
                }
            }
        }
        
        // Показываем все файлы из test_files/ (включая зашифрованные)
        if (fs::exists("test_files") && fs::is_directory("test_files")) {
            for (const auto& entry : fs::directory_iterator("test_files")) {
                if (entry.is_regular_file()) {
                    string filename = "test_files/" + entry.path().filename().string();
                    files.push_back(filename);
                }
            }
        }
        
        // Выводим список с красивыми иконками
        for (size_t i = 0; i < files.size(); i++) {
            string icon = "📄";
            if (files[i].find(".encrypted") != string::npos) icon = "🔒";
            else if (files[i].find("_decrypted") != string::npos) icon = "🔓";
            else if (files[i].find(".bmp") != string::npos || files[i].find(".png") != string::npos) icon = "🖼️";
            else if (files[i].find(".wav") != string::npos) icon = "🎵";
            else if (files[i].find(".avi") != string::npos) icon = "🎬";
            else if (files[i].find(".dat") != string::npos) icon = "📦";
            
            cout << setw(2) << (i + 1) << ". " << icon << " " << files[i];
            
            // Показываем размер файла
            try {
                auto size = fs::file_size(files[i]);
                cout << " (" << size << " байт)";
                if (size > 1024 * 1024) {
                    cout << " [" << fixed << setprecision(2) << size / (1024.0 * 1024.0) << " MB]";
                } else if (size > 1024) {
                    cout << " [" << fixed << setprecision(2) << size / 1024.0 << " KB]";
                }
            } catch (...) {
                cout << " (размер неизвестен)";
            }
            cout << endl;
        }
        
    } catch (const exception& e) {
        cout << "❌ Ошибка чтения директории: " << e.what() << endl;
        return "";
    }
    
    if (files.empty()) {
        cout << "📭 Файлы не найдены!" << endl;
        cout << "💡 Создайте тестовые файлы с помощью опции 5 в главном меню." << endl;
        return "";
    }
    
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "🎯 Выберите файл (1-" << files.size() << ") или 0 для отмены: ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        choice = 0;
    }
    cin.ignore();
    
    if (choice < 1 || choice > static_cast<int>(files.size())) {
        cout << "⚠️  Отменено пользователем." << endl;
        return "";
    }
    
    return files[choice - 1];
}

int CryptoSystem::chooseAlgorithm() {
    cout << "\n🔧 ВЫБЕРИТЕ АЛГОРИТМ ШИФРОВАНИЯ:" << endl;
    cout << "1. 🔄 RC4 (поточный шифр)" << endl;
    cout << "2. 🛡️  AES-128 CFB (промышленный стандарт)" << endl;
    cout << "3. 📊 Бинарный Виженер (блочный шифр)" << endl;
    cout << "Ваш выбор (1-3): ";
    
    int c;
    cin >> c;
    cin.ignore();
    
    if (c < 1 || c > 3) {
        cout << "⚠️  Неверный выбор! Используется RC4 по умолчанию." << endl;
        return RC4;
    }
    
    return c;
}

void CryptoSystem::clearScreen() {
    system("clear");
}

// Методы для работы с мультимедиа
string CryptoSystem::getFileType(const string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != string::npos) {
        string ext = filename.substr(pos + 1);
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        return ext;
    }
    return "unknown";
}

string CryptoSystem::getFileIcon(const string& filename) {
    string ext = getFileType(filename);
    
    if (ext == "txt" || ext == "md" || ext == "log") return "📄";
    if (ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp" || ext == "gif") return "🖼️";
    if (ext == "mp3" || ext == "wav" || ext == "flac" || ext == "ogg") return "🎵";
    if (ext == "mp4" || ext == "avi" || ext == "mkv" || ext == "mov") return "🎥";
    if (ext == "pdf") return "📕";
    if (ext == "zip" || ext == "rar" || ext == "7z") return "📦";
    if (ext == "encrypted") return "🔒";
    if (ext == "cpp" || ext == "h" || ext == "py" || ext == "js") return "💻";
    
    return "📁";
}

void CryptoSystem::showFileInfo(const string& filename) {
    try {
        if (fs::exists(filename)) {
            auto size = fs::file_size(filename);
            auto ftime = fs::last_write_time(filename);
            
            cout << "\n📋 ИНФОРМАЦИЯ О ФАЙЛЕ:" << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
            cout << "📁 Имя файла: " << filename << endl;
            cout << "📏 Размер: " << size << " байт";
            
            if (size > 1024 * 1024) {
                cout << " (" << fixed << setprecision(2) << size / (1024.0 * 1024.0) << " MB)";
            } else if (size > 1024) {
                cout << " (" << fixed << setprecision(2) << size / 1024.0 << " KB)";
            }
            cout << endl;
            
            cout << "🏷️  Тип: " << getFileIcon(filename) << " " << getFileType(filename) << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        }
    } catch (const exception& e) {
        cout << "⚠️  Не удалось получить информацию о файле: " << e.what() << endl;
    }
}

bool CryptoSystem::isImageFile(const string& filename) {
    string ext = getFileType(filename);
    return ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp" || ext == "gif";
}

bool CryptoSystem::isAudioFile(const string& filename) {
    string ext = getFileType(filename);
    return ext == "mp3" || ext == "wav" || ext == "flac" || ext == "ogg";
}

bool CryptoSystem::isVideoFile(const string& filename) {
    string ext = getFileType(filename);
    return ext == "mp4" || ext == "avi" || ext == "mkv" || ext == "mov";
}

bool CryptoSystem::isTextFile(const string& filename) {
    string ext = getFileType(filename);
    return ext == "txt" || ext == "md" || ext == "log" || ext == "cpp" || ext == "h" || ext == "py";
}

// Создание мультимедиа тестов
void CryptoSystem::createTestImage() {
    cout << "🖼️  Создание тестового BMP изображения..." << endl;
    
    const string filename = "test_files/test_image.bmp";
    fs::create_directories("test_files");
    
    // Простое BMP изображение 100x100 пикселей
    const int width = 100, height = 100;
    const int padding = (4 - (width * 3) % 4) % 4;
    const int fileSize = 54 + (width * 3 + padding) * height;
    
    vector<unsigned char> bmp(fileSize, 0);
    
    // BMP заголовок
    bmp[0] = 'B'; bmp[1] = 'M';
    *(int*)&bmp[2] = fileSize;
    *(int*)&bmp[10] = 54;
    *(int*)&bmp[14] = 40;
    *(int*)&bmp[18] = width;
    *(int*)&bmp[22] = height;
    *(short*)&bmp[26] = 1;
    *(short*)&bmp[28] = 24;
    
    // Пиксели (градиент)
    int offset = 54;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = offset + y * (width * 3 + padding) + x * 3;
            bmp[index] = (x * 255) / width;     // Blue
            bmp[index + 1] = (y * 255) / height; // Green
            bmp[index + 2] = 128;               // Red
        }
    }
    
    writeBinaryFile(filename, bmp);
    cout << "✅ Создан: " << filename << " (размер: " << fileSize << " байт)" << endl;
}

void CryptoSystem::createTestAudio() {
    cout << "🎵 Создание тестового WAV файла..." << endl;
    
    const string filename = "test_files/test_audio.wav";
    fs::create_directories("test_files");
    
    // Простой WAV файл с синусоидой 440Hz (нота La)
    const int sampleRate = 44100;
    const int duration = 2; // 2 секунды
    const int numSamples = sampleRate * duration;
    const int dataSize = numSamples * 2; // 16-bit mono
    const int fileSize = 44 + dataSize;
    
    vector<unsigned char> wav(fileSize);
    
    // WAV заголовок
    memcpy(&wav[0], "RIFF", 4);
    *(int*)&wav[4] = fileSize - 8;
    memcpy(&wav[8], "WAVE", 4);
    memcpy(&wav[12], "fmt ", 4);
    *(int*)&wav[16] = 16; // fmt size
    *(short*)&wav[20] = 1; // PCM
    *(short*)&wav[22] = 1; // mono
    *(int*)&wav[24] = sampleRate;
    *(int*)&wav[28] = sampleRate * 2; // byte rate
    *(short*)&wav[32] = 2; // block align
    *(short*)&wav[34] = 16; // bits per sample
    memcpy(&wav[36], "data", 4);
    *(int*)&wav[40] = dataSize;
    
    // Генерация синусоиды 440Hz
    const double frequency = 440.0;
    for (int i = 0; i < numSamples; i++) {
        double time = (double)i / sampleRate;
        double amplitude = sin(2.0 * M_PI * frequency * time) * 16383;
        short sample = (short)amplitude;
        *(short*)&wav[44 + i * 2] = sample;
    }
    
    writeBinaryFile(filename, wav);
    cout << "✅ Создан: " << filename << " (размер: " << fileSize << " байт)" << endl;
}

void CryptoSystem::createTestVideo() {
    cout << "🎥 Создание тестового AVI файла..." << endl;
    
    const string filename = "test_files/test_video.avi";
    fs::create_directories("test_files");
    
    // Минимальный AVI заголовок (без реальных видеоданных)
    vector<unsigned char> avi = {
        // RIFF заголовок
        'R', 'I', 'F', 'F', 0x20, 0x10, 0x00, 0x00, 'A', 'V', 'I', ' ',
        // LIST hdrl
        'L', 'I', 'S', 'T', 0x10, 0x10, 0x00, 0x00, 'h', 'd', 'r', 'l',
        // Добавляем минимальные заголовки AVI
        'a', 'v', 'i', 'h', 0x38, 0x00, 0x00, 0x00,
        0x40, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    
    // Добавляем немного "видеоданных"
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    
    for (int i = 0; i < 1000; i++) {
        avi.push_back(static_cast<unsigned char>(dis(gen)));
    }
    
    writeBinaryFile(filename, avi);
    cout << "✅ Создан: " << filename << " (размер: " << avi.size() << " байт)" << endl;
}

void CryptoSystem::createLargeTextFile() {
    cout << "📊 Создание большого текстового файла..." << endl;
    
    const string filename = "test_files/large_text.txt";
    fs::create_directories("test_files");
    
    ofstream file(filename);
    if (file.is_open()) {
        file << "🔐 ТЕСТОВЫЙ БОЛЬШОЙ ТЕКСТОВЫЙ ФАЙЛ (Kenpach1Zaracki - 2025)\n";
        file << "═══════════════════════════════════════════════════════════\n\n";
        
        // Генерируем текст для достижения ~1MB
        const vector<string> sentences = {
            "Это строка для тестирования криптографических алгоритмов.",
            "AES-128 CFB является современным стандартом шифрования.",
            "RC4 представляет собой классический поточный шифр.",
            "Бинарный Виженер демонстрирует принципы блочного шифрования.",
            "Криптографическая система должна обеспечивать надежную защиту данных.",
            "Тестирование производительности алгоритмов на больших файлах критично.",
            "Каждый алгоритм имеет свои преимущества и области применения.",
            "Безопасность современных систем зависит от качества шифрования."
        };
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, sentences.size() - 1);
        
        for (int i = 0; i < 50000; i++) {
            file << setw(6) << i + 1 << ". " << sentences[dis(gen)] << "\n";
            
            if ((i + 1) % 1000 == 0) {
                file << "\n--- Блок " << (i + 1) / 1000 << " (строки " << i - 999 << "-" << i + 1 << ") ---\n\n";
            }
        }
        
        file << "\n═══════════════════════════════════════════════════════════\n";
        file << "📋 СТАТИСТИКА ФАЙЛА:\n";
        file << "- Создан: " << __DATE__ << " " << __TIME__ << "\n";
        file << "- Автор: Kenpach1Zaracki\n";
        file << "- Назначение: Тестирование криптографических алгоритмов\n";
        file << "═══════════════════════════════════════════════════════════\n";
        
        file.close();
        
        auto size = fs::file_size(filename);
        cout << "✅ Создан: " << filename << " (размер: " << size << " байт / " 
             << fixed << setprecision(2) << size / (1024.0 * 1024.0) << " MB)" << endl;
    } else {
        cout << "❌ Ошибка создания файла!" << endl;
    }
}