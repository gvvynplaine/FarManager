//-------------------------------------------------------------------
//
//   CCCC   MM   MM  EEEEEE  MM   MM            v. 2.01
//  C    C  M M M M  E       M M M M    ��������  �������������
//  C       M  M  M  EEEE    M  M  M     ������ ��� ����������
//  C    C  M     M  E       M     M    ��������-���������������
//   CCCC   M     M  EEEEEE  M     M           ����������
//
//  ������� �஡��� ��ࠢ����� ( �.55 )
//  ���३ �.���쬠����
//
//  �ᯮ�짮�����:
//  --------------
//        - ᪮����� � ࠡ���� ��४��� 䠩� CMEM.CPP;
//        - ������� � �஥�� 䠩� CMEM.CPP;
//        - �� 㬮�砭�� �ணࠬ�� ࠡ�⠥� � 100
//          �����६���� ��।�����묨 㪠��⥫ﬨ,
//          �᫨ ��� ����室��� �������� �� ���祭��
//          Options->Compiler->Code generation->Defines
//          MAX_POINTERS=##;
//        - ��᫥ ����砭�� ࠡ��� ��襩 �ணࠬ��
//          �� ��᪥ �㤥� ᮧ��� 䠩� CMEM.RPT,
//          ����� ��⮨� �� "��ॢ�" ��।������
//          �����.
//-------------------------------------------------------------------
#include <windows.h>

#include <alloc.h>
#include <new.h>
#include <mem.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <process.h>

#if     !defined(MAX_POINTERS)
#define MAX_POINTERS 8096       // ���ᨬ��쭮� �᫮ �맮��� NEW
#endif

#define MEM_TO0( __nBL )  memset( __nBL,   0, sizeof __nBL )

extern unsigned _stklen = 43210U;

// ����⥫� ////////////////////////////////////////////////////////
enum flag      { Off, On, End = -1 };
enum line_char { U='\xDA', D='\xC0', H='\xC4',
                 V='\xB3', C='\xC5', S=' ' };

typedef void ( *pvf)();

//static HANDLE FARHeapForNew=NULL;

void GetNameEXE( char name[] )
{
    GetModuleFileName(NULL,name,512);
    char *ptr=strrchr(name,'.');
    if(ptr)
    {
      *ptr='\0';
      strcat(name,".rpt");
    }
}

// ���ᠭ�� ����� ����� ////////////////////////////////////////////
struct HeapBlock {
    void      *Addr;         // ����
    DWORD      SizeHOST,     // ������ - ����襭��
               SizeALLOC;    //        - ��।������
    flag       Status;       // ����� �������
    int        NCall;        // ����� � time_call
    // ������⢮ ����� --------------------------------------------
    DWORD      MemBefore,    // �� ��।������
               MemLater;     // ��᫥ �᢮��������
};

// �����, ����஫����騩 � ��ࠡ��뢠�騩 �訡�� ��।������ �����
class ControlMem {
public:
    ControlMem( void );                // ���������
    ~ControlMem( void );               // ��������

    int  search( void  * );        // ���� ����
    int  search_free( void );          // ���� ᢮������� �����
    // ��ॣ�㦥��� �������� ������� ��।������ ����� ------
    friend void  *operator new( size_t );
    friend void   operator delete( void  *);
    friend void  *operator new[]( size_t );
    friend void   operator delete[]( void  *);

private:
    struct HeapBlock HBL[ MAX_POINTERS ]; // ���ᨢ ����⥫�� ������
    static flag      StatusClass; // ����� ������⢨� �����
                                 // On-��, Off-���
    static flag      CloseBlock;  // ����� "������ �� �।��騩
                                 // ����" On-��, Off-���
    FILE            *rpt;    // �����⥫� ��⮪� 䠩�� ����
    static int       Meter;  // ���稪 �맮��� new & delete
    line_char        ch;     // ������ �����

    flag    time_call[ MAX_POINTERS*2 ];  // ���冷� �맮���
                                         // ����権 � �������
    int     find_state( void );           // �����頥� �����
                                         // � time_call[]
    void    state_end( void );           // ���⠢��� �ਧ��� ����
    // ��ࠡ�⪠ �訡�� ��।������ ����� ------------------------
    pvf  old_handler;   // �����⥫� �� ����� �㭪��
                       // ��ࠡ�⪨ �訡�� ��।������
    // �㭪樨 �ନ஢���� ���⮢ --------------------------------
    void open_r( void );     // ����⨥
    void close_r( void );    // �����⨥
    void out_mem  ( int );   // ������ ���ᨬ��쭮�� �����
    void out_size ( int );   // ������ �뤥������ �����
    void out_addr ( int );   // ����� �����
    void out_tab  ( int = -1 );   // �����
    void out_space( void );  // �஡��
    void out_open ( int, int = 0 );   // ����⨥ �����
    void out_close( int, int = 0 );   // �����⨥ �����
    void out_unknown( void * );    // ��������� ����
    void out_heap( void );   // �뢮��� ���ﭨ� �������᪨ ��।��塞��
                             // ������ �����
};

// ���樠������ static /////////////////////////////////////////////
flag ControlMem::StatusClass = Off;    // ����� ��ࠡ�⪨ ���������
flag ControlMem::CloseBlock  = Off;    // ��� �������� ������
int  ControlMem::Meter       = 0;      // ���稪 �맮���

// ������� ����� ��ࠡ�⪨ //////////////////////////////////////
ControlMem MemAlloc;

// ��������� ����� ��ࠡ�⪨ /////////////////////////////////////
ControlMem::ControlMem( void ) {
    ControlMem::StatusClass = On;
    MEM_TO0( HBL );
    MEM_TO0( time_call );
             time_call[0] = End;   // End - �ਧ��� ����
    open_r();
}

// ����⨥ 䠩�� ���� ///////////////////////////////////////////
// �ਭ樯 ࠡ���:
//     � ��砥 ������������ ᮧ����� 䠩�� - stderr
//-------------------------------------------------------------------
void ControlMem::open_r( void ) {
    char n[512] = "";
    HANDLE hFile;
    GetNameEXE( n );

    if( (rpt = fopen( n, "wt" )) == NULL )
         rpt = stderr;
    fprintf( rpt,
  "+-----------------------------------------------------------+\n"
  "|Control Memory Allocation                                  |\n"
  "+-----------------------------------------------------------+\n\n"
    );
}

// �����⨥ 䠩�� ࠯��� ///////////////////////////////////////////
void ControlMem::close_r( void ) {
    if (rpt != stderr)
        fclose( rpt );
}

// ������ ���ᨬ��쭮�� ᢮������� ����� ////////////////////////////
void ControlMem::out_mem( int n ) {
  switch( HBL[ n ].Status )
  {
    case  On:
      fprintf( rpt, "[%lu]\n", ( DWORD )HBL[ n ].MemBefore );
      break;
    case Off:
      fprintf( rpt, "[%lu]\n", ( DWORD)HBL[ n ].MemLater );
      break;
  }
}

// ����訢���� � ॠ�쭮 ��।������ ࠧ���� ����� "n" //////////
void ControlMem::out_size( int n ) {
    fprintf( rpt, "          Size: %lu(%lu)\n",
         ( DWORD )HBL[ n ].SizeHOST,
         ( DWORD )HBL[ n ].SizeALLOC
    );
}

// ���� ����� //////////////////////////////////////////////////////
void ControlMem::out_addr( int n ) {
  fprintf( rpt, "%c%Fp{\n", ch=U, HBL[ n ].Addr );
}

// ����� ��⮨� �� ���⨪����� ����� � ᮮ⢥��⢨� � time_call //
void ControlMem::out_tab( int d ) {
    int i=0;
    if(d != -1) d = HBL[ d ].NCall;
    while( time_call[ i ]!=End ){
         if (d==-1 || i<d)
              if( time_call[ i ] ) ch = V;
              else ch = S;
         else if( i==d ) ch = D;
         else if( i>d )
              if( time_call[ i ] ) ch = C;
              else ch = H;
         putc( ch, rpt ); i++;
    }
}

// ���⠥� �஡�� //////////////////////////////////////////////////
void ControlMem::out_space( void ) {
    putc( ' ', rpt );
}

// ���⠥� ���ଠ�� �� ���뢠�饬�� ����� //////////////////////
void ControlMem::out_open( int n,int typs ) {
    if( !ControlMem::CloseBlock ){
         out_tab(); out_space();
         if(typs) fprintf(rpt, " new[] ");
         else     fprintf(rpt, " new " );
         out_mem( n );
    }
    out_tab(); out_addr( n );
    HBL[ n ].NCall = MemAlloc.find_state();
    time_call[ HBL[ n ].NCall ] = On;
    out_tab(); out_size( n );
}

// ���⠥� ���� ����뢠�饣��� �����, ����� �� ���뢠��� ///////
void ControlMem::out_unknown( void  *p ) {
    out_tab(); fprintf( rpt, "<%Fp>{?}\n", p );
}

// ����뢠�� ���� "n" ///////////////////////////////////////////////
void ControlMem::out_close( int n, int typs) {
    out_tab( n ); putc( '}', rpt );
    if(typs) fprintf(rpt, " delete[] ");
    else     fprintf(rpt, " delete " );
    out_mem( n );
    time_call[ HBL[ n ].NCall ] = Off;
    state_end();
}

// ���ଠ�� � �������᪨ ��।��塞�� ������ ����� ///////////
void ControlMem::out_heap( void ) {
    struct heapinfo hi;
    int      i = 0;

    fprintf( rpt, "\nHeap:\n" );
    fprintf( rpt, "������������������Ŀ\n");
    fprintf( rpt, "� # � Size  �Status�\n" );
    fprintf( rpt, "������������������Ĵ\n" );
    hi.ptr = NULL;
    while( heapwalk(&hi ) == _HEAPOK )
         fprintf( rpt, "�%3d�%7lu� %4s �\n",
              ++i,
              (DWORD)hi.size,
              hi.in_use ? "used" : "free"
         );
    fprintf( rpt, "��������������������\n" );

    if(heapcheck() == _HEAPCORRUPT)
         fprintf( rpt, "\nHeap is corrupted.\n" );
    else
         fprintf( rpt, "\nHeap is OK.\n" );
}

// �������� ����� ��ࠡ�⪨ //////////////////////////////////////
ControlMem::~ControlMem( void ) {
    ControlMem::StatusClass = Off;
    out_heap();
    close_r();
  //  set_new_handler( old_handler );
}

// �����頥� ����� � time_call[] ����� i ///////////////////////////
int ControlMem::find_state( void ) {
    int k=0, i=0;
    while( time_call[i]!=End )
         if( time_call[i++]==On ) k = i;
    time_call[ k ] = Off; time_call[ k+1 ] = End;
    return k;
}

// ���⠢��� �ਧ��� ���� //
void ControlMem::state_end( void ) {
    int i=0, k;
    while( time_call[i++]!=End );
    k=(--i);
    while( i>=0 ){
         switch( time_call[ i ] ){
              case  On: return;
              case Off: time_call[ k ] = Off;
                        time_call[ i ] = End;
                        k=i;
         }
         i--;
    }
}

// ���� ���ଠ樨 � ����� /////////////////////////////////////////
// ��।�����:
//     p-���� �����
// �����頥�:
//     ����� ����� (i) ��� -1, �᫨ �� �� ������
//-------------------------------------------------------------------
int ControlMem::search( void  *p ) {
    for( int i=0; i<MAX_POINTERS; i++ )
        if (HBL[ i ].Addr == p)
            return i;
    return -1;
}

// ���� ᢮������� ����⥫� ///////////////////////////////////////
int ControlMem::search_free( void ) {
    int i = 0;
    do{
        if (HBL[ i ].Status == Off)
            return i;
    }while(++i < MAX_POINTERS);
    return -1;
}


// ��室�� ������ new ////////////////////////////////////////////
void  *o_NEW( size_t s ) {
    extern new_handler _new_handler;
    void  *p;
    s = s ? abs( s ) : 1;
    while ( (p = malloc( s )) == NULL && _new_handler != NULL )
        _new_handler();
    return p;
}

// ��ॣ�㦥��� ������ new ///////////////////////////////////////
// �ਭ樯 ࠡ���:
//   �᫨ ����� ��ࠡ�⪨ ���������, ࠡ�⠥� ��� ��몭������ new
//-------------------------------------------------------------------
#define coreleft()	0x7FFF8
void  *operator new( size_t size_block ) {
    int        i;
    void  *ptr;
    DWORD      mb = coreleft();

    ptr = o_NEW( size_block );
    if( ControlMem::StatusClass ){
         if( (i=MemAlloc.search_free()) == -1 ){
                  ControlMem::StatusClass = Off;
                  MemAlloc.out_heap();
                  MemAlloc.close_r();
              fprintf(stderr, "\nStack of pointers is full.\n");
              abort(); //exit(0);
         }
         if(!FARHeapForNew) FARHeapForNew=GetProcessHeap();
         MemAlloc.HBL[ i ].SizeHOST  = ( DWORD )size_block;
         MemAlloc.HBL[ i ].SizeALLOC = HeapSize(FARHeapForNew,0,ptr);
         MemAlloc.HBL[ i ].Status    = On;
         MemAlloc.HBL[ i ].MemBefore = mb;
         MemAlloc.HBL[ i ].Addr      = ptr;
         MemAlloc.out_open( i );
    }
    ControlMem::CloseBlock = Off;
    return ptr;
}

void * operator new[]( size_t size_block )
{
    int        i;
    void  *ptr;
    DWORD      mb = coreleft();

    ptr = o_NEW( size_block );
    if( ControlMem::StatusClass ){
         if( (i=MemAlloc.search_free()) == -1 ){
                  ControlMem::StatusClass = Off;
                  MemAlloc.out_heap();
                  MemAlloc.close_r();
              fprintf(stderr, "\nStack of pointers is full.\n");
              abort(); //exit(0);
         }
         if(!FARHeapForNew) FARHeapForNew=GetProcessHeap();
         MemAlloc.HBL[ i ].SizeHOST  = ( DWORD )size_block;
         MemAlloc.HBL[ i ].SizeALLOC = HeapSize(FARHeapForNew,0,ptr);
         MemAlloc.HBL[ i ].Status    = On;
         MemAlloc.HBL[ i ].MemBefore = mb;
         MemAlloc.HBL[ i ].Addr      = ptr;
         MemAlloc.out_open( i ,1 );
    }
    ControlMem::CloseBlock = Off;
    return ptr;
}

// ��室�� ������ delete /////////////////////////////////////////
void o_DELETE( void  *ptr ) {
    if( ptr ) free( ptr );
}

// ��ॣ�㦥��� ������ delete ////////////////////////////////////
// �ਭ樯 ࠡ���:
// �᫨ ����� ��ࠡ�⪨ ���������, ࠡ�⠥� ��� ��몭������ delete
//-------------------------------------------------------------------
void operator delete( void  *ptr ) {
    int        i;
    o_DELETE( ptr );
    if( ControlMem::StatusClass ){
         if( (i=MemAlloc.search( ptr )) == -1 ){
              MemAlloc.out_unknown( ptr ); return;
         }else{
              MemAlloc.HBL[ i ].MemLater = coreleft();
              MemAlloc.HBL[ i ].Status = Off;
              MemAlloc.out_close( i );
         }
    }
    ControlMem::CloseBlock = On;
}
void operator delete[]( void *ptr )
{
    int        i;
    o_DELETE( ptr );
    if( ControlMem::StatusClass ){
         if( (i=MemAlloc.search( ptr )) == -1 ){
              MemAlloc.out_unknown( ptr ); return;
         }else{
              MemAlloc.HBL[ i ].MemLater = coreleft();
              MemAlloc.HBL[ i ].Status = Off;
              MemAlloc.out_close( i ,1 );
         }
    }
    ControlMem::CloseBlock = On;
}


/*
VOID GlobalMemoryStatus(

    LPMEMORYSTATUS lpBuffer 	// pointer to the memory status structure
   );

typedef struct _MEMORYSTATUS { // mst
    DWORD dwLength;        // sizeof(MEMORYSTATUS)
    DWORD dwMemoryLoad;    // percent of memory in use
    DWORD dwTotalPhys;     // bytes of physical memory
    DWORD dwAvailPhys;     // free physical memory bytes
    DWORD dwTotalPageFile; // bytes of paging file
    DWORD dwAvailPageFile; // free bytes of paging file
    DWORD dwTotalVirtual;  // user bytes of address space
    DWORD dwAvailVirtual;  // free user bytes

} MEMORYSTATUS, *LPMEMORYSTATUS;
*/
/*
204800
1413120
*/