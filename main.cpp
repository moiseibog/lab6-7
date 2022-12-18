#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

int magic_num() {
    static unsigned int seed{ 3856 };
    seed = 8253729 * seed + 2396403;
    int a = seed % 10;
    return a;
}

std::string magic_nums(int len) {
    std::string s_num;
    if (len == 4) {
        int a1 = magic_num();
        if (a1 == 0) {
            while (a1 == 0) {a1 = magic_num();}}
        int a2 = magic_num();
        int a3 = magic_num();
        int a4 = magic_num();
        s_num += '0' + a1; s_num += '0' + a2; s_num += '0' + a3; s_num += '0' + a4;
        return s_num;
    } else if (len == 5) {
        int a1 = magic_num();
        if (a1 == 0) {
            while (a1 == 0) {a1 = magic_num();}}
        int a2 = magic_num();
        int a3 = magic_num();
        int a4 = magic_num();
        int a5 = magic_num();
        s_num += '0' + a1; s_num += '0' + a2; s_num += '0' + a3; s_num += '0' + a4; s_num += '0' + a5;
        return s_num;
    } 
    return s_num;
}

class generator {
    protected:
        char s; //sex
        std::string birth_date; //date of birth
        std::string n; //magic number
    public:
        virtual void set_sex(char s_given) = 0; //virtual for set sex of student
        virtual void set_birth_date(int dd, int mm, int yyyy) = 0; //virtual for birth date of student
        virtual void set_magic_n() = 0; // virtual for making random number
        virtual std::string ticket(char s_given, int dd, int mm, int yyyy) = 0;
};

class MIEM : public generator { //ticket SYYYYMMDDNNNNNC
    public:
        void set_sex(char s_given) override {
            if (s_given == 'M') {s = '8';
            } else if (s_given == 'W') {s = '4';}}
        void set_birth_date(int dd, int mm, int yyyy) override {
            std::string birth = "11111111";
            int d1 = dd / 10; int d2 = dd % 10;
            int m1 = mm / 10; int m2 = mm % 10;
            int y1 = yyyy / 1000; int y2 = (yyyy / 100) % 10; 
            int y3 = (yyyy / 10) % 10; int y4 = yyyy % 10;
            birth[0] = '0' + y1; birth[1] = '0' + y2; birth[2] = '0' + y3; birth[3] = '0' + y4;
            birth[4] = '0' + m1; birth[5] = '0' + m2; birth[6] = '0' + d1; birth[7] = '0' + d2;
            birth_date = birth;
        }
        void set_magic_n() override {
            n = magic_nums(5);
        }
        std::string ticket(char s_given, int dd, int mm, int yyyy) override {
            set_sex(s_given);
            set_birth_date(dd, mm, yyyy);
            set_magic_n();
            std::string ticket_miem = "0";
            ticket_miem[0] = s;
            ticket_miem = ticket_miem + birth_date + n;
            int sum = 0;
            for (int i = 0; i < 14; i++) {
                int k = ticket_miem[i] - '0';
                sum += (i+1)*k;
            }
            for (int i = 0; i < 10; i++) {
                if (((sum+(i*15)) % 11) == 0) {
                    ticket_miem += '0' + i;
                } 
            }
            return ticket_miem;
        }
};

class MGTUU : public generator { //ticket SYYYYMMDDNNNNC
    public:
        void set_sex(char s_given) override {
            if (s_given == 'M') {s = '2';
            } else if (s_given == 'W') {s = '1';}}
        void set_birth_date(int dd, int mm, int yyyy) override {
            std::string birth = "11111111";
            int d1 = dd / 10; int d2 = dd % 10;
            int m1 = mm / 10; int m2 = mm % 10;
            int y1 = yyyy / 1000; int y2 = (yyyy / 100) % 10; 
            int y3 = (yyyy / 10) % 10; int y4 = yyyy % 10;
            birth[0] = '0' + y1; birth[1] = '0' + y2; birth[2] = '0' + y3; birth[3] = '0' + y4;
            birth[4] = '0' + m1; birth[5] = '0' + m2; birth[6] = '0' + d1; birth[7] = '0' + d2;
            birth_date = birth;
        }
        void set_magic_n() override {
            n = magic_nums(4);
        }
        std::string ticket(char s_given, int dd, int mm, int yyyy) override {
            set_sex(s_given);
            set_birth_date(dd, mm, yyyy);
            set_magic_n();
            std::string ticket_mgtuu = "0";
            ticket_mgtuu[0] = s;
            ticket_mgtuu = ticket_mgtuu + birth_date + n;
            int sum = 0;
            for (int i = 0; i < 13; i++) {
                int k = ticket_mgtuu[i] - '0';
                sum += (i+1)*k;
            }
            for (int i = 0; i < 10; i++) {
                if (((sum+(i*14)) % 10) == 0) {
                    ticket_mgtuu += '0' + i;
                } 
            }
            return ticket_mgtuu;
        }
};

class TemplateGenerator {
    public:
        generator* templateGenerator(std::string name_) {
            if (name_ == "MIEM") {
                MIEM* new_ticket_MIEM = new MIEM;
                return new_ticket_MIEM;
            } else if (name_ == "MGTUU") {
                MGTUU* new_ticket_MGTUU = new MGTUU;
                return new_ticket_MGTUU;
            }
            exit(1);
        }
};

int main(int argc, char* argv[]) {
    bool mtofile = 0;
    bool mfromfile = 0;
    std::string tofile_name;
    std::string fromfile_name;
    if (argc != 1) {
        if (std::strcmp(argv[1], "--tofile") == 0) {
            mtofile = 1;
            if (argc != 2) {
                if (std::strcmp(argv[2], "--fromfile") == 0) {
                    mfromfile = 1;
                    tofile_name = "your_ticket.txt";
                    if (argc != 3) {
                        fromfile_name = argv[3];
                    } else {
                        std::cout << "Input Error!" << std::endl;
                        return -1;
                    }
                } else {
                    tofile_name = argv[2];
                    if (argc != 3) {
                        if (std::strcmp(argv[3], "--fromfile") == 0) {
                            mfromfile = 1;
                            if (argc != 4) {
                                fromfile_name = argv[4];
                            } else {
                                std::cout << "Input Error!" << std::endl;
                                return -1;
                            }
                        } else {
                            std::cout << "Input Error!" << std::endl;
                            return -1;
                        }
                    }
                }
            } else {
                tofile_name = "your_ticket.txt";
            }
        } else if (std::strcmp(argv[1], "--fromfile") == 0) {
            mfromfile = 1;
            if (argc != 2) {
                fromfile_name = argv[2];
                if (argc != 3) {
                    if (std::strcmp(argv[3], "--tofile") == 0) {
                        mtofile = 1;
                        if (argc != 4) {
                            tofile_name = argv[4];
                        } else {
                            tofile_name = "your_ticket.txt";
                        }
                    } else {
                        std::cout << "Input Error1" << std::endl;
                        return -1;
                    }
                }
            } else {
                std::cout << "Input Error!" << std::endl;
                return -1;
            }
        }
    }

    if (mfromfile) {
        std::ifstream fromfile(fromfile_name);
        if (!fromfile) {
            std::cout << "Input Error" << std::endl; 
            return -1;
        }
        std::string sex{};
        char sex_given;
        std::string univercity{};
        int dd, mm, yyyy;
        fromfile >> univercity >> sex >> yyyy >> mm >> dd;
        if (sex == "man") {sex_given = 'M';} else if (sex == "woman") {sex_given = 'W';} else {std::cout << "Sex uncorrected!" << std::endl;}

        TemplateGenerator templateGEN;
        std::string SB_1 = templateGEN.templateGenerator(univercity)->ticket(sex_given, dd, mm, yyyy);
        
        if (mtofile) {
            std::ofstream tofile(tofile_name);
            if (!tofile) {
                std::cout << "Input Error" << std::endl; 
                return -1;
            }
            tofile << "Your ticket: " << SB_1 << std::endl;
        } else {
            std::cout << "Your ticket: " << SB_1 << std::endl;
        }
    }

    if (!mfromfile) { // input: univercity_sex_yyyy_mm_dd
        std::string sex{};
        char sex_given;
        std::string univercity{};
        int dd, mm, yyyy;
        std::cin >> univercity >> sex >> yyyy >> mm >> dd;
        if (sex == "man") {sex_given = 'M';} else if (sex == "woman") {sex_given = 'W';} else {std::cout << "Sex uncorrected!" << std::endl;}

        TemplateGenerator templateGEN;
        std::string SB_1 = templateGEN.templateGenerator(univercity)->ticket(sex_given, dd, mm, yyyy);

        if (mtofile) {
            std::ofstream tofile(tofile_name);
            if (!tofile) {
                std::cout << "Input Error" << std::endl; 
                return -1;
            }
            tofile << "Your ticket: " << SB_1 << std::endl;
        } else {
            std::cout << "Your ticket is: " << SB_1 << std::endl;
        }
    }
}