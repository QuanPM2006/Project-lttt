#include <iostream>
#include <vector>
using namespace std;

class Bit {
private:
    bool gia_tri; 

public:
    Bit(int v = 0) { 
       gia_tri = v; 
    }
    
    Bit operator+(const Bit& bit_kia) const { return Bit(gia_tri ^ bit_kia.gia_tri); } 
    bool operator==(const Bit& bit_kia) const { return gia_tri == bit_kia.gia_tri; }
    
    int laySo() const { 
        if (gia_tri == true) return 1;
        else return 0;
    }

    friend ostream& operator<<(ostream& os, const Bit& b) {
        os << b.laySo();
        return os;
    }
    friend istream& operator>>(istream& is, Bit& b) {
        int v; is >> v;
        b = Bit(v); 
        return is;
    }
};

class BinaryVector {
private:
    vector<Bit> danh_sach_bit;

public:
    BinaryVector(int kich_thuoc = 0) { danh_sach_bit.assign(kich_thuoc, Bit(0)); }

    int doDai() const { return danh_sach_bit.size(); }
    
    Bit& operator[](int vi_tri) { return danh_sach_bit[vi_tri]; }
    const Bit& operator[](int vi_tri) const { return danh_sach_bit[vi_tri]; }

    BinaryVector operator+(const BinaryVector& vector_kia) const {
        BinaryVector ket_qua(doDai()); 
        for (int i = 0; i < doDai(); ++i) {
            ket_qua[i] = danh_sach_bit[i] + vector_kia[i]; 
        }
        return ket_qua;
    }

    bool laVectorKhong() const {
        for (int i = 0; i < doDai(); ++i) {
            if (danh_sach_bit[i].laySo() == 1) return false; 
        }
        return true; 
    }

    friend ostream& operator<<(ostream& os, const BinaryVector& vec) {
        os << "(";
        for (int i = 0; i < vec.doDai(); ++i) {
            os << vec[i];
            if (i < vec.doDai() - 1) os << " "; 
        }
        os << ")";
        return os;
    }
};

class BinaryMatrix {
private:
    vector<BinaryVector> cac_hang;

public:
    int so_hang, so_cot;

    BinaryMatrix(int h, int c) {
        so_hang = h;
        so_cot = c;
        cac_hang.assign(h, BinaryVector(c));
    }

    BinaryVector& operator[](int r) { return cac_hang[r]; }
    const BinaryVector& operator[](int r) const { return cac_hang[r]; }

    BinaryVector rutMotCotRa(int vi_tri_cot) const {
        BinaryVector cot_moi(so_hang);
        for (int i = 0; i < so_hang; ++i) {
            cot_moi[i] = cac_hang[i][vi_tri_cot];
        }
        return cot_moi;
    }

    friend istream& operator>>(istream& is, BinaryMatrix& m) {
        for(int i = 0; i < m.so_hang; ++i) {
            for(int j = 0; j < m.so_cot; ++j) {
                Bit b; is >> b;
                m.cac_hang[i][j] = b;
            }
        }
        return is;
    }
    
    friend ostream& operator<<(ostream& os, const BinaryMatrix& m) {
        for (int i = 0; i < m.so_hang; ++i) {
            for (int j = 0; j < m.so_cot; ++j) {
                os << m[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }
};

class LinearBlockCode {
private:
    BinaryMatrix ma_tran_H;
    int d_min;
    vector<int> danh_sach_cot_dmin; 

    bool thuChonCot(int so_luong_cot_can_tim, int cot_dang_xet, BinaryVector tong_hien_tai, vector<int>& cac_cot_da_chon) {
        int so_cot_con_lai = ma_tran_H.so_cot - cot_dang_xet;
        int so_cot_da_nhat = cac_cot_da_chon.size();
        
        if (so_cot_da_nhat + so_cot_con_lai < so_luong_cot_can_tim) {
            return false;
        }
        if (cac_cot_da_chon.size() == so_luong_cot_can_tim) {
            return tong_hien_tai.laVectorKhong(); 
        }
        if (cot_dang_xet >= ma_tran_H.so_cot) return false;

        bool ket_qua_nhanh_1 = thuChonCot(so_luong_cot_can_tim, cot_dang_xet + 1, tong_hien_tai, cac_cot_da_chon);
        if (ket_qua_nhanh_1 == true) return true; 

        cac_cot_da_chon.push_back(cot_dang_xet); 
        BinaryVector cot_vua_rut = ma_tran_H.rutMotCotRa(cot_dang_xet);
        BinaryVector tong_moi = tong_hien_tai + cot_vua_rut;
        
        bool ket_qua_nhanh_2 = thuChonCot(so_luong_cot_can_tim, cot_dang_xet + 1, tong_moi, cac_cot_da_chon);
        if (ket_qua_nhanh_2 == true) return true;
        
        cac_cot_da_chon.pop_back();
        return false;
    }

    void tinhDMin() {
        for (int w = 1; w <= ma_tran_H.so_cot; ++w) {
            BinaryVector tong_ban_dau(ma_tran_H.so_hang); 
            vector<int> danh_sach_chon;
            
            if (thuChonCot(w, 0, tong_ban_dau, danh_sach_chon) == true) {
                d_min = w; 
                danh_sach_cot_dmin = danh_sach_chon; 
                return; 
            }
        }
    }

public:
    LinearBlockCode(const BinaryMatrix& H) : ma_tran_H(H), d_min(-1) {
        tinhDMin();
    }

    void inLoiGiaiTuLuan() {
        cout << "Ma tran kiem tra H (" << ma_tran_H.so_hang << "x" << ma_tran_H.so_cot << "):\n" << ma_tran_H;
        cout << "\nTim khoang cach Hamming nho nhat (d_min):\n";
        
        for (int w = 1; w < d_min; ++w) {
            cout << "- Khong tim thay to hop " << w << " cot nao co tong bang vector 0.\n";
        }
        
        cout << "- Tim thay to hop " << d_min << " cot phu thuoc tuyen tinh. Cu the la cac cot: ";
        for (int i = 0; i < danh_sach_cot_dmin.size(); ++i) {
            cout << danh_sach_cot_dmin[i] + 1; 
            if (i < danh_sach_cot_dmin.size() - 1) cout << ", ";
        }
        cout << ".\n";
        
        cout << "\nPhep cong XOR cua " << d_min << " cot nay:\n";
        
        for (int i = 0; i < danh_sach_cot_dmin.size(); ++i) {
            int vi_tri = danh_sach_cot_dmin[i];
            BinaryVector cot = ma_tran_H.rutMotCotRa(vi_tri);
            cout << "      Cot " << vi_tri + 1 << ":  " << cot << "\n";
        }

        cout << "      Phep tinh: ";
        for (int i = 0; i < danh_sach_cot_dmin.size(); ++i) {
            int vi_tri = danh_sach_cot_dmin[i];
            BinaryVector cot = ma_tran_H.rutMotCotRa(vi_tri);
            
            cout << cot;
            if (i < danh_sach_cot_dmin.size() - 1) {
                cout << " + "; 
            }
        }
        
        BinaryVector vector_khong(ma_tran_H.so_hang); 
        cout << " = " << vector_khong << "\n\n";
        
        cout << "=> Khoang cach nho nhat: d_min = " << d_min << "\n\n";

        cout << "Kha nang phat hien va sua loi:\n";
        cout << "- Kha nang phat hien loi (e): d_min - 1 = " << d_min - 1 << " (bit).\n";
        cout << "- Kha nang sua loi (t): (d_min - 1) / 2 = " << (d_min - 1) / 2 << " (bit).\n";
        
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int so_hang, so_cot;
    while (cin >> so_hang >> so_cot) {
        BinaryMatrix H(so_hang, so_cot);
        cin >> H; 

        LinearBlockCode bo_ma_khoi(H);
        
     
        bo_ma_khoi.inLoiGiaiTuLuan();
    }
    return 0;
}
