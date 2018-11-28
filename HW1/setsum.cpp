#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
using namespace std;


void reverse(string& s) {
    string r="";
    for(int i=s.size()-1; i>=0; --i)
        r+=s[i];

    s=r;
}

void stringAdder(string& x, string& y, string& r) {
    unsigned int carry=0, num1=0, num2=0, num3=0;
    r=""; //clear out the result
    reverse(x);    reverse(y);

    for(int i=0; i<y.size(); ++i) {
        if(i>=x.size()) {
            num3=stoi(y.substr(i, 1));
            num3+=carry;
            if(num3>=10) {
                num3%=10;
                carry=1;
            }
            else
                carry=0;
        }
        else {
            num1=stoi(x.substr(i, 1));
            num2=stoi(y.substr(i, 1));
            num3=(num1+num2+carry)%10;
            if(num1+num2+carry<10)
                carry=0;
            else
                carry=1;
        }
        
        r+=num3;
        num1=num2=num3=0;
    }

    if(x.size()>y.size()) {
        for(int j=y.size(); j<x.size(); ++j) {
            num3=stoi(x.substr(j, 1))+carry;
            if(num3>=10) {
                num3%=10;
                carry=1;
            }
            else
                carry=0;

            r+=num3;
            num3=0;
        }
    }

    if(carry!=0)
        r+=carry;

    reverse(r);
}

bool equalstr(string& x, string& y) {
    if(x.size()!=y.size())
        return false;
    for(int i=0; i<x.size(); ++i)
        if(x[i]!=y[i])
            return false;

    return true;
}

int main(int argc, char** argv) {

    ifstream input("Numbers.txt");
    if (!input.good()) {
        cerr << "Can't open " << argv[3] << " to read.\n";
          exit(1);
    }

    vector<string> nums;
    vector<pair<vector<int>, string> > sums;
    vector<int> x;
    string temp;
    for(int i=0; i<100; ++i) {
        input >> temp;
        nums.push_back(temp);
        x.push_back(i);
        sums.push_back(make_pair(x, nums[i]));
        x.clear();
    }

    string r="";
    for(int j=0; j<99; ++j) {
        for(int k=j+1; k<100; ++k) {
            x.push_back(j);
            x.push_back(k);
            r="";
            stringAdder(nums[j], nums[k], r);
            
            sums.push_back(make_pair(x, r));
        }
        x.clear();
    }

    for(int i=0; i<sums.size()-1; ++i) {
        for(int j=i+1; j<sums.size(); ++j) {
            if(equalstr(sums[i].second, sums[j].second)) {
                for(int x=0; x<sums[i].first.size(); ++x)
                    cout<<sums[i].first[x]<<"   ";
                cout<<"\n\n";
                for(int y=0; y<sums[j].first.size(); ++y)
                    cout<<sums[j].first[y]<<"   ";
                return 0;
            }
        }
    }
    return 0;
}

    


    


