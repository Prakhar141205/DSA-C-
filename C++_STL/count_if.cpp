count_if(start_iterator, end_iterator, condition)


vector<int> arr = {1,2,3,4,5};

int cnt = count_if(arr.begin(), arr.end(),
                   [](int x){
                       return x % 2 == 0;
                   });
/*


| Algorithm   | Purpose               |
| ----------- | --------------------- |
| `sort`      | custom sorting        |
| `count_if`  | count condition       |
| `find_if`   | find matching element |
| `for_each`  | perform action        |
| `remove_if` | remove conditionally  |
| `any_of`    | any true?             |
| `all_of`    | all true?             |
| `none_of`   | none true?            |

*/

auto it = find_if(v.begin(), v.end(),
                  [](int x){
                      return x > 10;
                  });