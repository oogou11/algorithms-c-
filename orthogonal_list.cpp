// 十字链表类结点CLNode的定义
template<class T>
class CLNode
{
    public:
        int ROW,COL; //数据域
        T VAL;
        CLNode<T> *LEFT, *UP; //指针域
        CLNode(){           //构造函数
            ROW=COL=-1; 
            LEFT=UP=NULL;
        }
        CLNode(int r, int c, T v):ROW(r), COL(c), VAL(v){LEFT=UP=NULL;}

};
//稀疏矩阵
template<class T>
class SparseMatrix_C
{
    private:
        int Rows, Cols, Count;  //稀疏矩阵的行数、列数、非零元素个数
        CLNode<T> ** CLROW;     //行表头数组
        CLNode<T> **CLCOL;      //列表头数组
    public:
        SparseMatrix_C(int Mrows, int Cols, int Mcount);
        SparseMatrix_C<T>& BaseOperation(int Baserow, int Basecol); //主步骤操作
        int get_Rows() const{return Rows;} //返回矩阵行数 
        int get_Cols() const{return Cols;} //返回矩阵列数
};

//十字链表的构造函数
template<class T>
SparseMatrix_C<T>::SparseMatrix_C(int Mrows, int Mcols, int Mcount)
{
    if(Mrows<=0||Mcols<=0){         //判断矩阵下标是否合法
        std::cout << "bad initialzier" << std::endl;
        exit(1);
    }
    if(Mrows==1&&Mcols==1){         //规定1*1的矩阵不合法
        std::cout << "bad initialzier" << std::endl;
        exit(1);
    } 
    Rows = Mrows; Cols = Mcols; Count=Mcount;
    //申请空间
    CLROW = new CLNode<T>*[Rows];
    CLCOL = new CLNode<T>*[Cols];
    //初始化
    int i;
    for(i=0;i<Rows;i++){
        CLROW[i]=new CLNode<T>();
        CLROW[i]->LEFT=CLROW[i];
    }
    for(i=0;i<Cols;i++){
        CLCOL[i]=new CLNode<T>();
        CLCOL[i]->UP=CLCOL[i];
    }
};

//稀疏矩阵的主步骤操作，稀疏矩阵的表示方式为正交链表
template<class T>
SparseMatrix_C<T> &SparseMatrix_C<T>::BaseOperation(int I0, int J0)
{
    //SP1:初始化
    CLNode<T>*temp = CLROW[I0]->LEFT;
    while (temp->COL!=J0)
    {
        temp=temp->LEFT;
    }
    const T Alpha = 1.0/temp->VAL;
    temp->VAL = Alpha;
    CLNode<T> * P0 = CLROW[I0];
    CLNode<T> * Q0 = CLCOL[J0]; 
    CLNode<T> * PTR[100];
    //SP2: 处理主行
    P0 = P0 -> LEFT;
    int J = P0 -> COL;
    while (J!=-1)
    {
        PTR[J] = CLCOL[J];
        P0->VAL*=Alpha;
        P0=P0->LEFT;
        J=P0->COL;
    }
    //SP3: 找新行I，并指定P1
    while (1)
    {
        Q0=Q0->UP;
        int I = Q0->ROW;
        if(I<0){
            return *this;
        }
        if(I==I0){
            continue;
        }
        CLNode<T> *P=CLROW[I];
        CLNode<T> *P1 = P->LEFT;
        //SP4：确定新列J
        do{
            P0=P0->LEFT;
            J=P0->COL;
            if(J<0){
                break;
            }
            if(J==J0){
                continue;
            }
            //SP5: P1所指元素所在的列与J列比较
            while (P1->COL>J)
            { 
                P=P1;
                P1=P->LEFT;
            } 
            if(P1->COL==J){ 
                //SP7: 主步骤操作
                P1->VAL-=Q0->VAL*P0->VAL;
                
                if(P1->VAL==0){
                    //SP8:删除0元素
                    PTR[J]->UP=P1->UP;
                    P->LEFT=P1->LEFT;
                    delete P1;
                    P1 = P->LEFT;
                }else{
                    PTR[J]=P1;
                    P=P1;
                    P1=P->LEFT;
                }
            }else{
                //SP6: 插入新元素
                CLNode<T> *X = new CLNode<T>;
                X->VAL=-Q0->VAL*P0->VAL;
                X->ROW=I;
                X->COL=J;
                X->LEFT=P1;
                X->UP=PTR[J]->UP;
                P->LEFT=X;
                P=X;
                PTR[J]->UP=X;
                PTR[J]=X;
            }
        }
        while (J>=0);
        Q0->VAL *= -Alpha; 
    }
}