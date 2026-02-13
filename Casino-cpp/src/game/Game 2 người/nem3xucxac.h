#include "..//..//lib//header.h"

void game_nem3xucxac(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    intennguoichoi1(nguoichoi);
    string tennguoichoi2; int solansaiten = 0; 
    bool hopletennguoichoi2 = false;
    do {
        cout << "\t(?) Nhập tên người chơi 2: ";
        getline(cin, tennguoichoi2);
        if(tennguoichoi2.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên người chơi !" << RESET << endl;
            solansaiten++;
            continue;
        } else if(tennguoichoi2 == nguoichoi->tentaikhoan 
               || tennguoichoi2 == nguoichoi->tennguoichoi){
            cout << YELLOW << "\t\t(!) Vui lòng đặt tên khác !" << RESET << endl;
            solansaiten++;
            continue;
        } else hopletennguoichoi2 = true;
    } while(!hopletennguoichoi2 && solansaiten < solansaitoida);
    if(solansaiten == solansaitoida){
        return;
    }
    int tongxucxac1 = 0; int tongxucxac2 = 0; 
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    system("cls");
    inbanner(bannernemxucxac);
    cout << "\n" << RED << "[GAME] " << RESET << "NÉM 3 XÚC XẮC" << "\n\n";

    // người chơi 1 ném    
    cout << "\t>> Lượt: " << YELLOW << nguoichoi->tentaikhoan << RESET << endl;
    cout << "\t>> Nhấn phím bất kỳ để ném xúc xắc..." << endl;
    _getch();
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); 
    loadraketqua(5); cout << endl;
    cout << "\tXúc xắc của " << YELLOW << nguoichoi->tentaikhoan << RESET;
    int xucxac1 = rand() % 6 + 1;
    int xucxac2 = rand() % 6 + 1;
    int xucxac3 = rand() % 6 + 1;
    tongxucxac1 = xucxac1 + xucxac2 + xucxac3;
    cout << ": [" << xucxac1 << "] [" << xucxac2 << "] [" << xucxac3 << "] --> " 
         << YELLOW << tongxucxac1 << RESET << " điểm" << endl; 
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matxucxac[xucxac1][i] + "        " + matxucxac[xucxac2][i] + "        " + matxucxac[xucxac3][i], WHITE);
        cout << endl;
    }
    cout << endl;

    // người chơi 2 ném
    cout << "\t>> Lượt: " << YELLOW << tennguoichoi2 << RESET << endl;
    cout << "\t>> Nhấn phím bất kỳ để ném xúc xắc..." << endl;
    _getch();
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); 
    loadraketqua(5); cout << endl;
    cout << "\tXúc xắc của " << YELLOW << tennguoichoi2 << RESET << RESET;
    int xucxac4 = rand() % 6 + 1;
    int xucxac5 = rand() % 6 + 1;
    int xucxac6 = rand() % 6 + 1;
    tongxucxac2 = xucxac4 + xucxac5 + xucxac6;
    cout << ": [" << xucxac4 << "] [" << xucxac5 << "] [" << xucxac6 << "] --> " 
         << YELLOW << tongxucxac2 << RESET << " điểm" << endl; 
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matxucxac[xucxac4][i] + "        " + matxucxac[xucxac5][i] + "        " + matxucxac[xucxac6][i], WHITE);
        cout << endl;
    }

    cout << endl;
    cout << YELLOW << "\tKết quả: " << RESET;
    if(tongxucxac1 > tongxucxac2){
        cout << YELLOW << nguoichoi->tentaikhoan << RESET 
             << " thắng - (" << tongxucxac1 << " > " << tongxucxac2 << ")";
    } else if(tongxucxac2 > tongxucxac1){
        cout << YELLOW << tennguoichoi2 << RESET 
             << " thắng - (" << tongxucxac2 << " > " << tongxucxac1 << ")";
    } else {
        cout << YELLOW << "Cả 2 cùng hòa " << RESET
             << " (" << tongxucxac1 << " = " << tongxucxac2 << ")";
    }
}