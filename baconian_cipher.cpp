#include <bits/stdc++.h>
using namespace std;

vector<string> v;
map<string, char> m;

void map_codes(char c)
{
    string s;
    int n = c - 97;
    if (!isalpha(c))
    {
        cout << c << " : " << endl;
        return;
    }

    if (isupper(c))
    {
        n = c - 65;
    }
    while (n)
    {
        if (n & 1)
        {
            s += 'b';
        }
        else
        {
            s += 'a';
        }
        n = n >> 1;
    }
    while (s.length() < 5)
    {
        s += 'a';
    }
    reverse(s.begin(), s.end());
    m.insert(make_pair(s, c));
}
void baconian_encode(char c)
{
    string s;
    int n = c - 97;
    if (!isalpha(c))
    {
        cout << c << " : " << endl;
        return;
    }

    if (isupper(c))
    {
        n = c - 65;
    }
    while (n)
    {
        if (n & 1)
        {
            s += 'b';
        }
        else
        {
            s += 'a';
        }
        n = n >> 1;
    }
    while (s.length() < 5)
    {
        s += 'a';
    }
    reverse(s.begin(), s.end());
    v.push_back(s);
    cout << c << " : " << s << endl;
}
char bacaonian_decode(string s)
{
    return m[s];
}
int main()
{
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for_each(alphabet, alphabet + 26, map_codes);
    string s;
    cout << "Text for Encryption: ";
    getline(cin, s);
    cout << "\tEncrypted Codes\t" << endl;
    for_each(s.begin(), s.end(), baconian_encode);
    string s_text;
    cout << "Supporting text: ";
    getline(cin, s_text);
    int counter = 0;
    for (auto c : v)
    {

        for (int i = 0; i < c.length(); i++)
        {
            while (!isalpha(s_text[counter]))
                counter++;
            if (c[i] == 'b')
            {
                s_text[counter] = toupper(s_text[counter]);
                counter++;
            }

            else
                counter++;
        }
    }
    s_text = s_text.substr(0, counter);
    cout << "Encrypted text : " << s_text << endl;
    cout << "Do you want to decrypt it? (y/n) : ";
    char c;
    cin >> c;
    if (c == 'y' || c == 'Y')
    {
        s = "";
        for (auto x : s_text)
        {
            if (isalpha(x))
            {
                if (isupper(x))
                    s += 'b';
                else if (islower(x))
                    s += 'a';
                else
                    continue;
            }
        }
        cout << "Decrypted Codes : " << s << endl;

        int len = s.length();
        int n = 0;
        string es = "";
        while (n <= len - 5)
        {
            string str = s.substr(n, 5);
            es += bacaonian_decode(str);
            n = n + 5;
        }
        cout << "Decrypted Text : " << es << endl;
    }
    else
        return 0;

    return 0;
}