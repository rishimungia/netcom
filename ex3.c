// Error Detection and Control mechanisms

//     1. Parity Check

#include <stdio.h>
#include <string.h>
int even_parity(int bits[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (bits[i] == 1)
        {
            count++;
        }
    }
    if (count % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int odd_parity(int bits[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (bits[i] == 1)
        {
            count++;
        }
    }
    if (count % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int n, bits[30], choice = 0;
    printf("Sender\n");
    printf("Enter bits number = ");
    scanf("%d", &n);
    printf("Enter bits = \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bits[i]);
    }
    printf("1)Even Parity \n2)Odd Parity \n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        bits[n] = even_parity(bits, n);
        printf("Even parity bit is %d \n", bits[n]);
    }
    else if (choice == 2)
    {
        bits[n] = odd_parity(bits, n);
        printf("odd parity bit is %d\n", bits[n]);
    }
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", bits[i]);
    }
    printf("\nReceiver\n");
    char rece[30];
    int c = 0;
    printf("Enter the data sent by sender = ");
    scanf("%s", rece);
    for (int i = 0; i < strlen(rece); i++)
    {
        if (rece[i] == '1')
        {
            c++;
        }
    }
    if (choice == 1)
    {
        printf("Even parity\n");
        if (c % 2 == 0)
        {
            printf("THE ACCEPTED BITS ARE \n");
            for (int i = 0; i < strlen(rece) - 1; i++)
            {
                printf("%c", rece[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Bits rejected\n");
        }
    }
    if (choice == 2)
    {
        printf("Odd Parity");
        if (c % 2 != 0)
        {
            printf("THE ACCEPTED BITS ARE:\n");
            for (int i = 0; i < strlen(rece) - 1; i++)
            {
                printf("%c", rece[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Bits rejected\n");
        }
    }
}

// 2. Checksum

#include <stdio.h>
int data1[10], data2[10], carry = 0, sum[10], temp[10];
void checksum(void);
int add(int a, int b)
{
    int c = 0;
    if (a == 1)
    {
        c++;
    }
    if (b == 1)
    {
        c++;
    }
    if (carry == 1)
    {
        c++;
    }
    if (c == 1)
    {
        carry = 0;
        return 1;
    }
    else if (c == 2)
    {
        carry = 1;
        return 0;
    }
    else if (c == 3)
    {
        carry = 1;
        return 1;
    }
    else
    {
        carry = 0;
        return 0;
    }
}
void sender()
{
    printf("Enter 1st part of 8-bit data= ");
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &data1[i]);
    }
    printf("Enter 2st part of 8-bit data = ");
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &data2[i]);
    }
    checksum();
    for (int i = 0; i < 8; i++)
    {
        temp[i] = sum[i];
    }
}
void checksum()
{
    for (int i = 8; i >= 0; i--)
    {
        sum[i] = add(data1[i], data1[i]);
    }
    printf("\nChecksum = ");
    for (int i = 0; i < 8; i++)
    {
        if (sum[i] == 0)
        {
            sum[i] = 1;
        }
        else
        {
            sum[i] = 0;
        }
        printf("%d", sum[i]);
    }
}
void receiver()
{
    int key = 0;
    printf("Enter 1st part of 8-bit = ");
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &data1[i]);
    }
    printf("Enter 2st part of 8-bit = ");
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &data2[i]);
    }
    checksum();
    for (int i = 0; i < 8; i++)
    {
        if (temp[i] != sum[i])
        {
            printf("\nCheck sum is not same, bits rejected\n");
            key = 1;
            break;
        }
    }
    if (key == 0)
    {
        printf("\nChecksum is same therefore bits accepted\n");
    }
}
int main()
{
    printf("SENDER\n");
    sender();
    printf("\nRECEIVER\n");
    receiver();
}

// 3. CRC
#include<stdio.h> 
int n, m, data[50], divisor[10], out[10];
int xor (int a, int b) {
    if (a == b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
} void append_zeros(int l, int n)
{
    for (int i = n; i < n + l - 1; i++)
    {
        data[i] = 0;
    }
}
void CRC()
{
    printf("Intermediate Divison Values\n");
    for (int i = 0; i < m - 1; i++)
    {
        if (data[0] == 1)
        {
            out[i] = xor(data[i + 1], divisor[i + 1]);
        }
        else
        {
            out[i] = xor(data[i + 1], 0);
        }
    }
    out[m - 1] = data[m];
    for (int i = 0; i < m; i++)
    {
        printf("%d", out[i]);
    }
    printf("\n");
    for (int j = m + 1; j < n + m; j++)
    {
        if (out[0] == 1)
        {
            for (int i = 0; i < m - 1; i++)
            {
                out[i] = xor(out[i + 1], divisor[i + 1]);
            }
        }
        else
        {
            for (int i = 0; i < m - 1; i++)
            {
                out[i] = xor(out[i + 1], 0);
            }
        }
        out[m - 1] = data[j];
        for (int i = 0; i < m; i++)
        {
            printf("%d", out[i]);
        }
        printf("\n");
    }
    printf("CRC = ");
    for (int i = 0; i < m - 1; i++)
    {
        printf("%d", out[i]);
    }
    printf("\n");
}
int main()
{
    printf("Enter the length of Data: ");
    scanf("%d", &n);
    printf("Enter the data = \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    printf("Enter the length of Divisor: ");
    scanf("%d", &m);
    printf("Enter Divisor= \n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &divisor[i]);
    }
    printf("\n***sender - Side***\n");
    printf("Number of zero's to be appended: %d \n", m - 1);
    append_zeros(m, n);
    printf("Data After appending: ");
    for (int i = 0; i < n + m - 1; i++)
    {
        printf("%d", data[i]);
    }
    printf("\n");
    CRC();
    for (int i = n; i < n + m - 1; i++)
    {
        data[i] = out[i - n];
    }
    printf("Generated message = ");
    for (int i = 0; i < n + m - 1; i++)
    {
        if (i == n)
        {
            printf(" | ");
        }
        printf("%d", data[i]);
    }
    printf("\n****Receiver_side**\n");
    printf("Enter the data received: \n");
    for (int i = 0; i < n + m - 1; i++)
    {
        scanf("%d", &data[i]);
    }
    CRC();
}
