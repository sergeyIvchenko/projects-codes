#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int freq = 1;
    char symbol;
    string NodeCode = "";
    double probability{};
    Node(char newc):symbol(newc){}
};

auto get_table(string msg){
    vector<Node> table;
    string unique = "";
    for(auto it : msg){
        if(unique.find(it)==string::npos){
            table.push_back(Node(it));
            unique += it;
        }
        else{
            int idx = unique.find(it);
            table[idx].freq++;
        }
    }
    sort(table.begin(), table.end(),[](Node l,Node r){
        return l.freq > r.freq;
    });
    int sum = msg.size();
    for_each(table.begin(), table.end(), [sum](Node& el){
        el.probability = 1.*el.freq/sum;
    });
    return table;
}
vector<string> codes;
void shannon_encoding(vector<Node>& table, string code, int sum){
    if(table.size() == 1){
        codes.push_back(code);
        return;
    }
    //cout << table.size();
    int left_sum = sum/2;
    int right_sum = sum - left_sum;
    vector<Node> leftvec(table.begin(), table.begin()+left_sum);
    vector<Node> rightvec(table.begin()+left_sum, table.end());
    shannon_encoding(leftvec,code + "1",left_sum);
    shannon_encoding(rightvec, code + "0", right_sum);
}
//SetConsoleOutputCP(CP_UTF8);
////ios_base::sync_with_stdio(false);
//string tmpmsg,mess;
//int way{};
//cout << "Виберіть варіант:" << endl;
//cout << "1 - Ручний запис" << endl;
//cout << "2 - Читання з файлу" << endl;
//double entropy{}, max_entropy{}, av_len{};
//cin >> way;
//cin.ignore();
//if(way == 1){
//cout << "Уведіть повідомлення:"<< endl;
//while(getline(cin,tmpmsg)){mess+=tmpmsg;}
//auto tmp = get_table(mess);
//shannon_encoding(tmp, "", tmp.size());
//for(int i=0;i<tmp.size();++i){
//cout << tmp[i].symbol <<" " << tmp[i].freq << " " << tmp[i].probability << " " << codes[i] << endl;
//}
//for(auto it: tmp){
//entropy -= it.probability*log2(it.probability);
//}
//max_entropy = log2(tmp.size());
//for(int i=0;i<tmp.size();++i){
//av_len += tmp[i].probability*codes[i].size();
//}
//}
//else if(way == 2){
//ifstream file("text.txt", ios::binary);
//ofstream encodedfile("result.txt");
//while(getline(file,tmpmsg)){
//mess+=tmpmsg;
//}
//auto tmp = get_table(mess);
//shannon_encoding(tmp,"",tmp.size());
//for(auto it: tmp){
//entropy -= it.probability*log2(it.probability);
//}
//max_entropy =log2(tmp.size());
//for(int i=0;i<tmp.size();++i){
//av_len += tmp[i].probability*codes[i].size();
//}
////        for(int i=0;i<tmp.size();++i){
////            cout << tmp[i].symbol <<" " << tmp[i].freq << " " << tmp[i].probability << " " << codes[i] << endl;
////        }
//for(int i=0;i<tmp.size();++i){
//for(int j=1;j<tmp[i].freq;++j)
//{
//auto temp = codes[i];
//codes[i].append(temp);
//}
//}
//copy(codes.begin(),codes.end(), ostream_iterator<string>{encodedfile});
//encodedfile.close();
//file.close();
//}
//
//cout << "Ентропія: " << entropy << endl;
//cout << "Максимальна ентропія: " << max_entropy << endl;
//cout << "Середня довжина: " << av_len << endl;
//system("pause");