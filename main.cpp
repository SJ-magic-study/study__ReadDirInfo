/************************************************************
ディレクトリの読み込み
	http://www.syuhitu.org/other/dir.html
************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h>
#include <string>

using namespace std;


/************************************************************
************************************************************/

/******************************
******************************/
void print_cnt( int cnt )
{
	int i;
	for ( i = 0; i < cnt; i++ ){
		putchar( '\t' );
	}
}

/******************************
******************************/
void foo( int cnt, const string dirname )
{
	DIR *pDir;
	struct dirent *pEnt;
	struct stat wStat;
	string wPathName;

	// ディレクトリを開く
	pDir = opendir( dirname.c_str() );
	if ( NULL == pDir ) {
		printf( "Error : in %s directoryt\n", dirname.c_str() );
		return ;
	}

	pEnt = readdir( pDir );
	while ( pEnt ) {
		// .と..は処理しない
		if ( strcmp( pEnt->d_name, "." ) && strcmp( pEnt->d_name, ".." ) ) {
		
			wPathName = dirname + "/" + pEnt->d_name;
			
			// ファイルの情報を取得
			if ( stat( wPathName.c_str(), &wStat ) ) {
				printf( "Failed to get stat %s \n", wPathName.c_str() );
				break;
			}
			
			if ( S_ISDIR( wStat.st_mode ) ) {
				// ディレクトリの場合
				print_cnt( cnt );
				printf( "Directory - %s\n", pEnt->d_name );
				foo( cnt + 1, wPathName );
			} else {
				// ファイルの場合
				print_cnt( cnt );
				printf( "File - %s\n", pEnt->d_name );
			}
		}
		
		// 次のファイルを検索する
		pEnt = readdir( pDir );
	}

	// ハンドルを閉じる
	closedir( pDir );
}

/******************************
******************************/
int main()
{
	foo( 0, "." );
	return 0;
}

