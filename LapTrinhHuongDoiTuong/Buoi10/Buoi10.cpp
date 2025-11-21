
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

enum LoaiPhuongTien
{
    XE_MAY = 1,
    OTO = 2,
    XE_TAI = 3
};

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

class PhuongTien {
public:
    string sohieu;
    int namsanxuat;
    double giaban;
    virtual void nhap() {
        cout << "THONG TIN CHI TIET:" << endl;
        cout << "\t+ So hieu: ";
        cin >> sohieu;
        cout << "\t+ Nam san xuat: ";
        cin >> namsanxuat;
        cout << "\t+ Gia ban: ";
        cin >> giaban;
    }
    virtual void xuat() {
        cout << "\t+ So hieu: " << sohieu << endl;
        cout << "\t+ Nam san xuat: " << namsanxuat << endl;
        cout << "\t+ Gia ban: " << giaban << endl;
    }
    virtual void ghiTapTin(ofstream& ofs) {   
        writeString(ofs, sohieu);
        ofs.write(reinterpret_cast<const char*> (&namsanxuat), sizeof(namsanxuat));
        ofs.write(reinterpret_cast<const char*> (&giaban), sizeof(giaban));
    }
    virtual void docTapTin(ifstream& ifs) {
        sohieu = readString(ifs);
        ifs.read(reinterpret_cast<char*>(&namsanxuat), sizeof(namsanxuat));        
        ifs.read(reinterpret_cast<char*>(&giaban), sizeof(giaban));
    }
};
class XeMay : public PhuongTien {
public:
    int dungtichxilanh;
    void nhap() override {
        PhuongTien::nhap();
        cout << "\t+ Dung tich xilanh: ";        
        cin >> dungtichxilanh;
    }
    void xuat() override {
        cout << "XE MAY:" << endl;
        PhuongTien::xuat();
        cout << "\t+ Dung tich xilanh: " << dungtichxilanh << endl;        
    }
    void ghiTapTin(ofstream& ofs) override {
        LoaiPhuongTien type = LoaiPhuongTien::XE_MAY;
        ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));    
        PhuongTien::ghiTapTin(ofs);
        ofs.write(reinterpret_cast<const char*> (&dungtichxilanh), sizeof(dungtichxilanh));
    }
    void docTapTin(ifstream& ifs) override {
        PhuongTien::docTapTin(ifs); 
        ifs.read(reinterpret_cast<char*>(&dungtichxilanh), sizeof(dungtichxilanh));
    }
};
class Oto : public PhuongTien {
public:
    int sochongoi;
    void nhap() override {
        PhuongTien::nhap();
        cout << "\t+ So cho ngoi: ";
        cin >> sochongoi;
    }
    void xuat() override {
        cout << "OTO:" << endl;
        PhuongTien::xuat();
        cout << "\t+ So cho ngoi: " << sochongoi << endl;
    }
    void ghiTapTin(ofstream& ofs) override {
        LoaiPhuongTien type = LoaiPhuongTien::OTO;
        ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
        PhuongTien::ghiTapTin(ofs);
        ofs.write(reinterpret_cast<const char*> (&sochongoi), sizeof(sochongoi));
    }
    void docTapTin(ifstream& ifs) override {
        PhuongTien::docTapTin(ifs);
        ifs.read(reinterpret_cast<char*>(&sochongoi), sizeof(sochongoi));
    }
};
class XeTai : public PhuongTien {
public:
    int taitrongtoida;
    void nhap() override {
        PhuongTien::nhap();
        cout << "\t+ Tai trong toi da: ";
        cin >> taitrongtoida;
    }
    void xuat() override {
        cout << "XE TAI:" << endl;
        PhuongTien::xuat();
        cout << "\t+ Tai trong toi da: " << taitrongtoida << endl;
    }
    void ghiTapTin(ofstream& ofs) override {
        LoaiPhuongTien type = LoaiPhuongTien::XE_TAI;
        ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
        PhuongTien::ghiTapTin(ofs);
        ofs.write(reinterpret_cast<const char*> (&taitrongtoida), sizeof(taitrongtoida));
    }
    void docTapTin(ifstream& ifs) override {
        PhuongTien::docTapTin(ifs);
        ifs.read(reinterpret_cast<char*>(&taitrongtoida), sizeof(taitrongtoida));
    }
};

class QLPTGT {
public:
    vector<PhuongTien*> dsPhuongTien;
    void themPhuongTien(PhuongTien* pt) {
        dsPhuongTien.push_back(pt);
        cout << "Them phuong tien thanh cong !!" << endl;
    }
    void timPhuongTien(string ms) {
        for (PhuongTien* pt : dsPhuongTien) {
            if (pt->sohieu == ms) {
                pt->xuat();
                return;
            }
        }
        cout << "Khong tim thay nhan su co ma so " << ms << endl;
    }
    double duToanThanhLy() {
        double tongtien = 0;
        for (PhuongTien* pt : dsPhuongTien) {
            double tam = pt->giaban - (2025 - pt->namsanxuat) * 0.2 * pt->giaban;
            if (tam > 0)
                tongtien += tam;
        }
        return tongtien;
    }
    void ghiTapTin() {
        ofstream ofs("24th.dla", ios::binary);
        if (!ofs) {
            cout << "Loi: Khong mo duoc tap tin de ghi" << endl;
            return;
        }
        for (PhuongTien* pt : dsPhuongTien) {
            pt->ghiTapTin(ofs);
        }
        ofs.close();
        cout << "Ghi du lieu thanh cong !!" << endl;
    }
    void docTapTin() {
        ifstream ifs("24th.dla", ios::binary);
        if (!ifs) {
            cout << "Loi: Khong mo duoc file de doc" << endl;
            return;
        }
        dsPhuongTien.clear();
        LoaiPhuongTien type;
        while (true) {
            ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
            if (ifs.eof()) {
                break;
            }
            PhuongTien* pt;
            if (type == LoaiPhuongTien::XE_MAY) {
                pt = new XeMay();
            }
            else if (type == LoaiPhuongTien::OTO) {
                pt = new Oto();
            }
            else if (type == LoaiPhuongTien::XE_TAI) {
                pt = new XeTai();
            }
            else {
                break;
            }
            pt->docTapTin(ifs);
            dsPhuongTien.push_back(pt);
        }
        ifs.close();
        cout << "Doc tap tin thanh cong !!" << endl;
    }
    ~QLPTGT() {
        for (PhuongTien* pt : dsPhuongTien) {
            delete pt;
        }
    }
};

int main()
{
    QLPTGT ql;
    do {
        system("cls");
        cout << "--- CHUONG TRINH QUAN LY PHUONG TIEN GIAO THONG ---" << endl;
        cout << "1. Them moi phuong tien" << endl;
        cout << "2. Tim kiem phuong tien theo so hieu" << endl;
        cout << "3. Du toan thanh ly xe" << endl;
        cout << "4. Luu danh sach" << endl;
        cout << "5. Doc danh sach" << endl;
        cout << "0. Thoat" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Chon chuc nang: ";
        int chucnang;
        cin >> chucnang;
        switch (chucnang)
        {
        case 1: {
            PhuongTien* pt;
            cout << "Nhap loai phuong tien (1 - Xe may; 2 - Oto; 3 - Xe tai): ";
            int type;
            cin >> type;
            if (type == LoaiPhuongTien::XE_MAY) {
                pt = new XeMay();
            }
            else if (type == LoaiPhuongTien::OTO) {
                pt = new Oto();
            }
            else if (type == LoaiPhuongTien::XE_TAI) {
                pt = new XeTai();
            }
            else {
                break;
            }
            pt->nhap();
            ql.themPhuongTien(pt);
            break;
        }
        case 2: {
            cout << "Nhap so hieu can tim: ";
            string sohieu;
            cin >> sohieu;
            ql.timPhuongTien(sohieu);
            break;
        }
        case 3: {
            cout << "Tong du toan tien thanh ly xe: " << ql.duToanThanhLy() << endl;
            break;
        }
        case 4: {
            ql.ghiTapTin();
            break;
        }
        case 5: {
            ql.docTapTin();
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Chuc nang khong ton tai !!" << endl;
            break;
        }
        cout << "Go enter de tiep tuc..." << endl;
        cin.ignore();
        cin.get();
    } while (true);
}
