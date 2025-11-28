
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


void writeString(ofstream& ofs, const string& str) {
    size_t len = str.length();
    ofs.write(reinterpret_cast<const char*> (&len), sizeof(len));
    ofs.write(str.c_str(), len);
}
string readString(ifstream& ifs) {
    size_t len;
    ifs.read(reinterpret_cast<char*> (&len), sizeof(len));
    if (!ifs.good()) {
        return "";
    }
    string str(len, '\0');
    ifs.read(&str[0], len);
    return str;
}
class NgayThangNam {
    int ngay, thang, nam;
};
class Phong {
    int maphong, dungluong;
    string tenphong;
    double dongia;
public:
    Phong(){}
    Phong(int a) {
        maphong = a;
    }
    int MaPhong() {
        return maphong;
    }
    void nhap() {
        cout << "THONG TIN PHONG:" << endl;
        cout << "\t+ Ma phong: ";
        cin >> maphong;
        cout << "\t+ Ten phong: ";
        cin >> tenphong;
        cout << "\t+ Don gia: ";
        cin >> dongia;
        cout << "\t+ Dung luong: ";
        cin >> dungluong;
    }
    void xuat() {
        cout << maphong << "\t\t" << tenphong << "\t\t" << dongia << "\t" << dungluong << endl;
    }
    void ghiTapTin(ofstream& ofs) {
        ofs.write(reinterpret_cast<const char*> (&maphong), sizeof(maphong));
        writeString(ofs, tenphong);
        ofs.write(reinterpret_cast<const char*> (&dongia), sizeof(dongia));
        ofs.write(reinterpret_cast<const char*> (&dungluong), sizeof(dungluong));
    }
    void docTapTin(ifstream& ifs) {
        tenphong = readString(ifs);
        ifs.read(reinterpret_cast<char*>(&dongia), sizeof(dongia));
        ifs.read(reinterpret_cast<char*>(&dungluong), sizeof(dungluong));
    }
};
class SinhVien {
    int masv;
    string hoten;
    NgayThangNam ngayvao;
    Phong phong;
};
class HoaDon {
    int mahd;
    Phong phong;
    NgayThangNam ngaylap;
};

class QLKTX {
    vector<Phong> dsPhong;  
    vector<SinhVien> dsSinhVien;
    vector<HoaDon> dsHoaDon;
public:
    void themPhong(Phong p) {
        dsPhong.push_back(p);
        cout << "Them phong thanh cong !!" << endl;
    }
    void xemPhong() {
        cout << "DANH SACH PHONG: " << endl;
        cout << "Ma phong\tTen phong\tDon gia\tDung luong" << endl;
        for (Phong p : dsPhong) {
            p.xuat();
        }
    }
    void xoaPhong(int ms) {
        int vt = 0;
        for (Phong p : dsPhong) {
            if (p.MaPhong() == ms) {
                dsPhong.erase(dsPhong.begin() + vt);
                cout << "Xoa phong thanh cong !!" << endl;
                return;
            }
            vt++;
        }
        cout << "Khong tim thay phong can xoa" << endl;
    }
    void ghiPhong() {
        ofstream ofs("phong.dla", ios::binary);
        if (!ofs) {
            cout << "Loi: Khong mo duoc tap tin de ghi" << endl;
            return;
        }
        for (Phong p : dsPhong) {
            p.ghiTapTin(ofs);
        }
        ofs.close();
        cout << "Ghi du lieu thanh cong !!" << endl;
    }
    void docPhong() {
        ifstream ifs("phong.dla", ios::binary);
        if (!ifs) {
            cout << "Loi: Khong mo duoc file de doc" << endl;
            return;
        }
        dsPhong.clear();       
        while (true) {
            int maphong;
            ifs.read(reinterpret_cast<char*>(&maphong), sizeof(maphong));
            if (ifs.eof()) {
                break;
            }
            Phong p(maphong);            
            p.docTapTin(ifs);
            dsPhong.push_back(p);
        }
        ifs.close();
        cout << "Doc tap tin thanh cong !!" << endl;
    }
};

void main()
{
    QLKTX ql;
    do {
        system("cls");
        cout << "---- QUAN LY KY TUC XA ----" << endl;
        cout << "1. Quan ly phong" << endl;
        cout << "2. Quan ly sinh vien" << endl;
        cout << "3. Quan ly hoa don" << endl;
        cout << "4. Bao cao" << endl;
        cout << "0. Thoat" << endl;
        cout << "---------------------------" << endl;
        cout << "Chon chuc nang: ";
        int chucnang;
        cin >> chucnang;
        switch (chucnang)
        {
        case 1:
        {
            do {
                system("cls");
                cout << "---- Quan ly phong ----" << endl;
                cout << "1. Them phong" << endl;
                cout << "2. Xem danh sach phong" << endl;
                cout << "3. Xoa phong" << endl;
                cout << "4. Ghi danh sach phong ra tap tin" << endl;
                cout << "5. Doc danh sach phong tu tap tin" << endl;
                cout << "0. Quay lai" << endl;
                cout << "-----------------------" << endl;
                cout << "Chon chuc nang: ";
                cin >> chucnang;
                if (chucnang == 0)
                    break;
                switch (chucnang)
                {
                case 1:
                {
                    Phong p;
                    p.nhap();
                    ql.themPhong(p);
                    break;
                }
                case 2: {
                    ql.xemPhong();
                    break;
                }
                case 3: {
                    cout << "Nhap ma phong can xoa: ";
                    int mp;
                    cin >> mp;
                    ql.xoaPhong(mp);
                    break;
                }
                case 4: {
                    ql.ghiPhong();
                    break;
                }
                case 5: {
                    ql.docPhong();
                    break;
                }
                default:
                    cout << "Chuc nang khong ton tai !!" << endl;
                    break;
                }
                cout << "Go enter de tiep tuc..." << endl;
                cin.ignore();
                cin.get();
            } while (true);
            break;
        }
        case 2: {
            do {
                system("cls");
                cout << "---- Quan ly sinh vien ----" << endl;
                cout << "1. Them sinh vien" << endl;
                cout << "2. Xem danh sach sinh vien" << endl;
                cout << "3. Xoa sinh vien" << endl;
                cout << "4. Ghi danh sach sinh vien ra tap tin" << endl;
                cout << "5. Doc danh sach sinh vien tu tap tin" << endl;
                cout << "0. Quay lai" << endl;
                cout << "-----------------------" << endl;
                cout << "Chon chuc nang: ";
                cin >> chucnang;
                if (chucnang == 0)
                    break;
                switch (chucnang)
                {
                case 1:
                {
                    break;
                }
                case 2: {
                    break;
                }
                case 3: {
                    break;
                }
                case 4: {
                    break;
                }
                case 5: {
                    break;
                }
                default:
                    cout << "Chuc nang khong ton tai !!" << endl;
                    break;
                }
                cout << "Go enter de tiep tuc..." << endl;
                cin.ignore();
                cin.get();
            } while (true);
            break;
        }
        case 3: {
            do {
                system("cls");
                cout << "---- Quan ly hoa don ----" << endl;
                cout << "1. Them hoa don" << endl;
                cout << "2. Xem danh sach hoa don" << endl;      
                cout << "3. Ghi danh sach hoa don ra tap tin" << endl;
                cout << "4. Doc danh sach hoa don tu tap tin" << endl;
                cout << "0. Quay lai" << endl;
                cout << "-----------------------" << endl;
                cout << "Chon chuc nang: ";
                cin >> chucnang;
                if (chucnang == 0)
                    break;
                switch (chucnang)
                {
                case 1:
                {
                    break;
                }
                case 2: {
                    break;
                }         
                case 3: {
                    break;
                }
                case 4: {
                    break;
                }
                default:
                    cout << "Chuc nang khong ton tai !!" << endl;
                    break;
                }
                cout << "Go enter de tiep tuc..." << endl;
                cin.ignore();
                cin.get();
            } while (true);
            break;
        }
        case 4: {
            break;
        }
        case 0: {
            return;
        }
        default:
            cout << "Chuc nang khong ton tai !!" << endl;
            break;
        }
        cout << "Go enter de tiep tuc..." << endl;
        cin.ignore();
        cin.get();
    } while (true);   
}
