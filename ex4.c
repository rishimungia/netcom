// Flow control mechanisms
// 1. Stop and Wait ARQ
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;
class timer
{
private:
    unsigned long begTime;

public:
    void start()
    {
        begTime = clock();
    }
    unsigned long elapsedTime()
    {
        return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
    }
    bool isTimeout(unsigned long seconds)
    {
        return seconds >= elapsedTime();
    }
};
int main()
{
    int frames[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned long seconds = 5;
    srand(time(NULL));
    timer t;
    cout << "Sender has to send frames : ";
    for (int i = 0; i < 10; i++)
        cout << frames[i] << " ";
    cout << endl;
    int count = 0;
    bool delay = false;
    cout << endl
         << "Sender\t\t\t\t\tReceiver" << endl;
    do
    {
        bool timeout = false;
        cout << "Sending Frame : " << frames[count];
        cout.flush();
        cout << "\t\t";
        t.start();
        if (rand() % 2)
        {
            int to = 24600 + rand() % (64000 - 24600) + 1;
            for (int i = 0; i < 64000; i++)
                for (int j = 0; j < to; j++)
                {
                }
        }
        if (t.elapsedTime() <= seconds)
        {
            cout << "Received Frame : " << frames[count] << " ";
            if (delay)
            {
                cout << "Duplicate";
                delay = false;
            }
            cout << endl;
            count++;
        }
        else
        {
            cout << "---" << endl;
            cout << "Timeout" << endl;
            timeout = true;
        }
        t.start();
        if (rand() % 2 || !timeout)
        {
            int to = 24600 + rand() % (64000 - 24600) + 1;
            for (int i = 0; i < 64000; i++)
                for (int j = 0; j < to; j++)
                {
                }
            if (t.elapsedTime() > seconds)
            {
                cout << "Delayed Ack" << endl;
                count--;
                delay = true;
            }
            else if (!timeout)
                cout << "Acknowledgement : " << frames[count] - 1 << endl;
        }
    } while (count != 10);
    return 0;
}

// 2. Go back N ARQ
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int w_size, no_of_frames;
int frames[30];
int a, no_of_tr;
void Sender()
{
    cout << "Enter the number of frames : ";
    cin >> no_of_frames;
    cout << "Enter the Window Size : ";
    cin >> w_size;
    cout << "Enter Frames :";
    for (int i = 0; i < no_of_frames; i++)
    {
        cin >> frames[i];
    }
}
int Reciever()
{
    int i = 1;
    while (i <= no_of_frames)
    {
        int a = 0;
        for (int j = i; j < i + w_size && j <= no_of_frames; j++)
        {
            cout << "Sent Frame " << j << ": ";
            cout << frames[j - 1];
            cout << endl;
            no_of_tr++;
        }
        for (int j = i; j < i + w_size && j <= no_of_frames; j++)
        {
            int flag = rand() % 2;
            if (!flag)
            {
                cout << "Acknowledgment for Frame ";
                cout << j;
                cout << "\n";
                a++;
            }
            else
            {
                cout << "Frame " << j << " Not Received\n";
                cout << "\n";
                cout << "Retransmit Window" << endl;
                break;
            }
        }
        cout << endl;
        i = i + a;
    }
    cout << "Total number of transmissions : ";
    cout << no_of_tr;
    cout << "\n";
    return 0;
}
int main()
{
    srand(time(NULL));
    Sender();
    Reciever();
    return 0;
}

// 3. Selective Repeat ARQ
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int w_size, no_of_frames;
int frames[70];
int random_frame(int w_size)
{
    int number;
    int up = w_size, low = 0;
    number = (rand() % (up - low + 1)) + low;
    return number;
}
void Sender()
{
    cout << "\n";
    cout << "SENDER'S SIDE:";
    cout << "\n";
    cout << "Enter Window Size:\n";
    cin >> w_size;
    cout << "Number of frames to transmit:\n";
    cin >> no_of_frames;
    cout << "Enter the " << no_of_frames << " frames: ";
    for (int i = 1; i <= no_of_frames; i++)
    {
        cin >> frames[i];
    }
}
void Receiver()
{
    cout << "\n";
    cout << "RECIEVER'S SIDE WITHOUT RANDOM FRAME:";
    cout << "\n";
    cout << "\nWith random acknowledgement,the order of frames are:\n";
    int a = random_frame(no_of_frames);
    cout << "Random - frame = ";
    cout << a;
    cout << "\n";
    if (a != no_of_frames)
    {
        for (int i = 1; i <= a; i++)
        {
            if (i % w_size == 0)
            {
                cout << frames[i];
                cout << "\n\n";
                cout << "Acknowledgement for the frames sent, are received by 
                        Sender.";
                        cout
                     << "\n";
            }
            else
                cout << frames[i];
            cout << " ";
            cout << "\n\n";
        }
        cout << "Acknowledgement for the frames sent, are received by Sender.";
        cout << "\n";
        for (int i = a + 1; i <= no_of_frames; i++)
        {
            int temp;
            temp = i - (a);
            if (temp % w_size == 0)
            {
                cout << frames[i];
                cout << "\n\n";
                cout << "Acknowledgement for the frames sent, are received by 
                        Sender.";
                        cout
                     << "\n";
            }
            else
                cout << frames[i];
            cout << " ";
            cout << "\n\n";
        }
    }
    else
    {
        for (int i = 1; i <= no_of_frames; i++)
        {
            if (i % w_size == 0)
            {
                cout << frames[i];
                cout << "\n\n";
                cout << "Acknowledgement for the frames sent, are received by 
                        Sender.";
                        cout
                     << "\n";
            }
            else
            {
                cout << frames[i];
                cout << " ";
                cout << "\n\n";
            }
        }
    }
    cout << "Acknowledgement for the frames sent, are received by Sender,";
}
int main()
{
    srand(time(NULL));
    Sender();
    Receiver();
    return 0;
}
