#include <iostream>
using namespace std;

bool parse(int jf) {
    bool k=false;

    do {
        if((jf%10==0)||(jf%10==1)||(jf%10==2)) {
            k=true;
            break;
        }
        jf=jf/10;
    }
    while(jf>0);
    return k;
}

int main() {
    int n[3],i=0;
    bool k1,k2,k=true;

    for(int j=0;j<3;j++) {
        cin >> n[j];
    }

    while(i<3) {
        k=true;
        for(int j=1;j<=n[i]/2;j++) {
            k1=parse(j);
            k2=parse(n[i]-j);
            if((k1==false)&&(k2==false)) {
                k=false;
                break;
            }
        }
        cout << k << endl;;
        i++;
    }

    return 0;
}
