#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <windows.h>

using namespace std;

class Sort {
private:
    double cost;
    vector<int> res_insert, res_bubble, res_select, res_shell, res_merge, res_merge2,
            res_quick, res_heap, res_count, res_count2, res_bucket, res_radix;
    LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER nEndTime;

public:
    double cal_used_time(int th, vector<int> array)
    {
        switch (th) {
            case 1:
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                res_insert = InsertSort(array);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;
            case 2:
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                res_bubble = BubbleSort(array);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;
            case 3:
                res_select = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                SelectSort(res_select);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;
            case 4:
                res_shell = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                ShellSort(res_shell);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;
            case 5:
                res_merge = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                MergeSort(res_merge);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 6:
                res_merge2 = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                MergeSort2(res_merge2);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 7:
                res_quick = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                QuickSort(res_quick, 0, res_quick.size()-1);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 8:
                res_heap = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                HeapSort(res_heap);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 9:
                res_count = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                CountSort(res_count, *max_element(res_count.begin(),res_count.end()));
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 10:
                res_count2 = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                CountSort2(res_count2);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 11:
                res_bucket = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                BucketSort(res_bucket);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            case 12:
                res_radix = array;
                QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
                QueryPerformanceCounter(&m_nBeginTime); // 获取时钟计数
                RadixSort(res_radix);
                QueryPerformanceCounter(&nEndTime);
                cost = (double)(nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart;
                break;

            default:
                break;

        }
        return cost;
    }
    void ShowArr(vector<int> arr)
    {
        if (arr.empty())
            return;
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << "\t";
        }
        cout << endl;
    }
    int min(int x, int y){
        return (x < y) ? x : y;
    }

//    1
//插入排序
    vector<int> InsertSort(vector<int> num)
    {
        int i;			//有序区间的最后一个元素的位置,i+1就是无序区间最左边元素的位置
        for(i = 0; i < num.size()-1; ++i){
            int tmp = num[i + 1];  //tmp是待插入到有序区间的元素,即无序区间最左边的元素
            int j = i;
            while(j >= 0 && tmp < num[j]){		//寻找插入的位置
                num[j + 1] = num[j];				//比tmp大的元素都往后移动
                --j;
            }
            num[j + 1] = tmp;
        }
        return num;
    }
//    2
//冒泡排序
    vector<int> BubbleSort(vector<int> num)
    {
        for(int i = 0; i < num.size() - 1; i++)
        {
            for(int j = 0; j < num.size() - i - 1; j++)
            {
                if(num[j] > num[j + 1])
                    swap(num[j],num[j + 1]);
            }
        }
        return num;
    }
//    3
//选择排序
    void SelectSort(vector<int> &a)
    {
        //对数组a排序,length是数组元素数量
        for( int i = 0; i < a.size(); i++ ) {
            // 找到从i开始到最后一个元素中最小的元素,k存储最小元素的下标.
            int k = i;
            for( int j = i + 1; j < a.size(); j++ ) {
                if( a[j] < a[k] ) { k = j; }
            }

            // 将最小的元素a[k] 和 开始的元素a[i] 交换数据.
            if( k != i ) {
                int temp;
                temp= a[k];
                a[k] = a[i];
                a[i] = temp;
            }
        }
    }
//    4
//希尔排序
    void ShellSort(vector<int> &vec)
    {
        // 希尔排序
        for(int gap=vec.size()/2;gap>0;gap/=2)
        {
            // 直接插入排序
            for(int i=gap;i<vec.size();++i)
            {
                int j=i;
                int tmp = vec[j];
                while(j-gap>=0 && vec[j-gap]>tmp)
                {
                    vec[j] = vec[j-gap];
//                    swap(vec[j-gap], vec[j]);
                    j -= gap;
                }
                vec[j] = tmp;
            }
        }
    }
//    5
//归并排序递归法
    void MergeSort(vector<int> &arr)
    {
        if (arr.size()<2)
            return;
        sortprocess(arr,0,arr.size()-1);
    }
    void merge(vector<int> &arr,int L,int mid,int R)
    {
        int *help = new int[R-L+1];
        int p1=L,p2=mid+1,i=0;
        while(p1<=mid && p2<=R)
        {
            help[i++] = arr[p1]>arr[p2] ? arr[p2++] : arr[p1++];
        }
        while(p1<=mid)
            help[i++] = arr[p1++];
        while(p2<=R)
            help[i++] = arr[p2++];

        for (int i=0;i<R-L+1;i++)
        {
            arr[L+i] = help[i];
        }
        delete []help;
    }
    void sortprocess(vector<int> &brr,int L,int R)
    {
        if (L < R)
        {
//            int mid = L + ((R-L)>>2);  //  (L+R)/2
            int mid = (L+R)/2;
            sortprocess(brr,L,mid);
            sortprocess(brr,mid+1,R);
            merge(brr,L,mid,R);
        }
    }

//    6
//归并排序非递归法
    void MergeSort2(vector<int> &data){
        int n = data.size();
        // 子数组的大小分别为1，2，4，8...
        // 刚开始合并的数组大小是1，接着是2，接着4....
        for (int i = 1; i < n; i += i) {
            //进行数组进行划分
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;
            //进行合并，对数组大小为 i 的数组进行两两合并
            while (right < n) {
                // 合并函数和递归式的合并函数一样
                merge(data, left, mid, right);
                left = right + 1;
                mid = left + i - 1;
                right = mid + i;
            }
            // 还有一些被遗漏的数组没合并，千万别忘了
            // 因为不可能每个字数组的大小都刚好为 i
            if (left < n && mid < n) {
                merge(data, left, mid, n - 1);
            }
        }
    }

//    7
//快速排序
    void QuickSort(vector<int> &data, int left, int right)
    {
        if (left > right)
            return;
        int j = partition(data, left, right);
        QuickSort(data, left, j - 1);
        QuickSort(data, j + 1, right);
    }
    int partition(vector<int> &data, int left, int right)  //找基准数 划分
    {
        int i = left + 1 ;
        int j = right;
        int temp = data[left];

        while(i <= j)
        {
            while (data[i] < temp)
            {
                i++;
            }
            while (data[j] > temp )
            {
                j--;
            }
            if (i < j)
                swap(data[i++], data[j--]);
            else i++;
        }
        swap(data[j], data[left]);
        return j;
    }

//    8
//堆排序
    void HeapSort(vector<int> &a)
    {
        int len = a.size();
        for (int i = len/2; i >= 0; --i)//从最后一个非叶子节点的父结点开始建堆
        {
            Heap_build(a,i,len);
        }

        for (int j = len-1; j > 0; --j)//j表示数组此时的长度，因为len长度已经建过了，从len-1开始
        {
            swap(a[0],a[j]);//交换首尾元素,将最大值交换到数组的最后位置保存
            Heap_build(a,0,j);//去除最后位置的元素重新建堆，此处j表示数组的长度，最后一个位置下标变为len-2
        }
    }
    void Heap_build(vector<int> &a,int root,int length)
    {
        int lchild = root*2+1;//根节点的左子结点下标
        if (lchild < length)//左子结点下标不能超出数组的长度
        {
            int flag = lchild;//flag保存左右节点中最大值的下标
            int rchild = lchild+1;//根节点的右子结点下标
            if (rchild < length)//右子结点下标不能超出数组的长度(如果有的话)
            {
                if (a[rchild] > a[flag])//找出左右子结点中的最大值
                {
                    flag = rchild;
                }
            }
            if (a[root] < a[flag])
            {
                //交换父结点和比父结点大的最大子节点
                swap(a[root],a[flag]);
                //从此次最大子节点的那个位置开始递归建堆
                Heap_build(a,flag,length);
            }
        }
    }
    // arr为输入的数组，n为数组长度，i为节点的序号void heapify(int arr[], int n, int i)
    void heapify(vector<int> &arr, int n, int i)
    {
        int largest = i; // Initialize largest as root
        int l = 2*i + 1; // left = 2*i + 1
        int r = 2*i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l] > arr[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && arr[r] > arr[largest])
            largest = r;

        // If largest is not root
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }
//    9
//    计数排序
    void CountSort(vector<int> &arr, int maxVal)
    {
        int len = arr.size();
        if (len < 1)
            return;
        vector<int> count(maxVal+1, 0);
        vector<int> tmp(arr);
        for (auto x : arr)
            count[x]++;
        for (int i = 1; i <= maxVal; ++i)
            count[i] += count[i - 1];
        for (int i = len - 1; i >= 0; --i) {
            arr[count[tmp[i]] - 1] = tmp[i];
            count[tmp[i]]--;				//注意这里要减1
        }
    }
//    10
//    计数排序
    void CountSort2(vector<int> &A)
    {
        int Max = *max_element(A.begin(), A.end());
        int Size = A.size();
        vector<int> B(Max+1, 0);
        int i, j, count = 0;
        for (i = 0; i < Size; i++) {
            j = A[i];
            B[j] += 1;
        }
        for (i = 0; i <= Max; i++) {
            if (B[i] > 0) {
                for (j = 0; j < B[i]; j++) {
                    A[count] = i;
                    count++;
                }
            }
        }
    }
//    11
//    桶排序
//    需要很久排序数组中元素的大小调整桶的规则
    void BucketSort(vector<int> &a)
    {
        int n = a.size();
        int **p = new int *[10];//p数组存放十个double指针，分为10个桶
        for (int i=0; i < 10; ++i)
        {
            p[i] = new int[100];//每个指针都指向一块10个double的数组，每个桶都可以包含100个元素
        }

        int count[10] = {0};//元素全为0的数组
        for (int i = 0; i < n; ++i)
        {
            int temp = a[i];
            int flag = temp/10 >= 10 ? 9: temp/10;//判断每个元素属于哪个桶
            p[flag][count[flag]] = temp;//将每个元素放入到对应的桶中，从0开始
            int j = count[flag]++;//将对应桶的计数加1

            //在本桶之中与之前的元素做比较，比较替换（插入排序）
            for (;j > 0 && temp < p[flag][j-1];--j)
            {
                p[flag][j] = p[flag][j-1];
            }
            p[flag][j] = temp;
        }

        //元素全部放完之后，需要进行重新链接的过程
        int k = 0;
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < count[i]; ++j)//桶中元素的个数count[i]
            {
                a[k++] = p[i][j];
            }
        }

        //申请内存的释放
        for (int i = 0 ; i<10 ;i++)
        {
            delete p[i];
            p[i] =NULL;
        }
        delete []p;
        p = NULL;
    }
//    12
//    基数排序
    void RadixSort(vector<int> &orderArray)
    {
        vector<queue<int>> container(10);
        for(int m = 0;m<3;m++){
            for(int i=0;i<orderArray.size();i++){
                int temp = orderArray[i];
                for(int j=0;j<m;j++) temp/=10; //取个位、十位、百位
                container[temp%10].push(orderArray[i]); //按上述位数投入相应容器
            }
            orderArray.clear(); //清空初始数组
            for(int i=0;i<10;i++){ // 将容器内的数按次序收集下来
                while(!container[i].empty()){
                    orderArray.push_back(container[i].front());
                    container[i].pop();
                }
            }
        }
    }
};

int main()
{
    Sort A;
    vector<int> a;
    int n = 100;
    while(n--)
    {
        a.push_back(rand() % 100);
    }

    cout << "InsertSort Used Time: " << A.cal_used_time(1, a) << endl;

    cout << "BubbleSort Used Time: " << A.cal_used_time(2, a) << endl;

    cout << "SelectSort Used Time: " << A.cal_used_time(3, a) << endl;

    cout << "ShellSort Used Time: " << A.cal_used_time(4, a) << endl;

    cout << "MergeSort Used Time: " << A.cal_used_time(5, a) << endl;

    cout << "MergeSort Non-Recursion Used Time: " << A.cal_used_time(6, a) << endl;

    cout << "QuickSort Used Time: " << A.cal_used_time(7, a) << endl;

    cout << "HeapSort Used Time: " << A.cal_used_time(8, a) << endl;

    cout << "CountSort Used Time: " << A.cal_used_time(9, a) << endl;

    cout << "CountSort2 Used Time: " << A.cal_used_time(10, a) << endl;

    cout << "BucketSort Used Time: " << A.cal_used_time(11, a) << endl;

    cout << "RadixSort Used Time: " << A.cal_used_time(12, a) << endl;

    return 0;
}