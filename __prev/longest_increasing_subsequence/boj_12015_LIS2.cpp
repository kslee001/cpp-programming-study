#include <iostream>
using namespace std;

int binary_search(int left, int right, int target, int* temp){
    int mid;
    while(left < right){          // left가 right보다 작을때까지만 지속 -> len >1 일 때 지속
        mid = (left+right)/2;     
        if(temp[mid]<target){     // target이 지금 잘라놓은 array(temp)의 중간보다 크다면 
            left = mid+1;         // -> right part
        }
        else{                     // 더 작다면 
            right = mid;          // -> left part
        }
    }
    return right;                 // 
}

int main(){
    int n; scanf("%d", &n);
    int arr[n]; for(int i=0; i<n; ++i){
        scanf("%d", &arr[i]);
    }
    int temp[n];
    
    
    temp[0] = arr[0];                   // STEP 1. temp 에 첫번째 array 원소 집어넣기
    int j = 0;                          
    for(int i=1; i<n; ++i){             // STEP 2. array의 2번째 원소부터 탐색 
        if(temp[j] < arr[i]){           // STEP 3. 지금까지 저장된 temp(가장 긴 수열)의 마지막 원소부터 비교
            temp[j+1] = arr[i];         //   -> 마지막 원소보다 지금 보고 있는 arr의 원소가 더 크다면, temp의 수열에 append
            j++;                        //   -> pointer 이동
        }
        else{
            int pos = binary_search(0, j, arr[i], temp);    // 더 작다면 binary search 실행 -> insert 할 자리를 찾는다.
                                                            // 1) binary search를 통해 update가 이루어지는 index를 반환하고
                                                            // 2) 그 지점에 지금 보고 있는 arr[i]를 입력
                                                            //   - 같은 숫자가 업데이트 되는 경우도 있고
                                                            //   - 다른 숫자가 업데이트 되는 경우도 있지만, 
                                                            //     이 경우에도 대소 관계에 영향은 없다 
                                                            //     ex. arr[i] = 2,  
                                                            //         temp   = [ 1, 3, 5, 7 ] 
                                                            //         ->       [ 1, "2", 5, 7]  (3 update)
            temp[pos]= arr[i];
        }
    }

    // arr  -> [ 1,2,1,3,2,5]
    // temp -> [ 1, 2, (1, else), 3, (2, else), 5 ]

    printf("%d", j+1);  // 현재 array의 마지막 원소 pointer+1 (length) 반환 
}