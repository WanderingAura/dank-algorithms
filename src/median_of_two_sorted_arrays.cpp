// LC4 Median of 2 sorted arrays
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> combinedArr(nums1.size() + nums2.size());

        int start1 = 0;
        int start2 = 0;
        int write = 0;

        while (start1 < nums1.size() || start2 < nums2.size()) {
            if (start1 >= nums1.size()) {
                combinedArr[write++] = nums2[start2++];
                continue;
            } else if (start2 >= nums2.size()) {
                combinedArr[write++] = nums1[start1++];
                continue;
            }
            if (nums1[start1] <= nums2[start2]) {
                combinedArr[write++] = nums1[start1++];
            } else {
                combinedArr[write++] = nums2[start2++];
            }
        }

        // we now have a combined sorted array.
        int combinedSize = combinedArr.size();
        if (combinedSize % 2 == 0) {
            return ((double)combinedArr[combinedSize/2 - 1] + (double)combinedArr[combinedSize/2])/2;
        } else {
            return (double)combinedArr[(combinedSize - 1)/2];
        }
    }

    double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int n = n1 + n2;
        if (n1 > n2) {
            return findMedianSortedArrays2(nums2, nums1);
        }

        if (n1 == 0) {
            if (n2 % 2 == 0) {
                return ((double)nums2[n2/2 - 1] + (double)nums2[n2/2])/2;
            }
            return nums2[(n2-1)/2];
        }

        int leftPartitionSize = (n + 1) / 2; // +1 so that it contains the median
            int low = 0, high = n1;
        for (int i = 0; i < 1000; i++) {
            int lSplitSize1 = (high + low) / 2;
            int lSplitSize2 = leftPartitionSize - lSplitSize1;
            
            int maxLeft1 = INT_MIN, maxLeft2 = INT_MIN, minRight1 = INT_MAX, minRight2 = INT_MAX;

            // is current partition valid?
            // if it is valid then return the median
            // if not then if maxLeft1 > minRight2 we need to check the left side of nums1
            // if maxLeft2 > minRight1 we need to check the right side of nums1

            if (lSplitSize1 > 0)
                maxLeft1 = nums1[lSplitSize1-1];
            if (lSplitSize2 > 0)
                maxLeft2 = nums2[lSplitSize2-1];
            if (lSplitSize1 < n1)
                minRight1 = nums1[lSplitSize1];
            if (lSplitSize2 < n2)
                minRight2 = nums2[lSplitSize2];

            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if (n % 2 == 0) {
                    return (double)(max(maxLeft1, maxLeft2) + min(minRight1, minRight2))/2;
                } else {
                    return max(maxLeft1, maxLeft2);
                }
            } else if (maxLeft1 > minRight2) {
                high = lSplitSize1;
            } else {
                low = lSplitSize1 + 1;
            }
        }

        cout << "error: max iterations exceeded" << endl; 
        return 0;
    }
};

int main() {
    Solution s;
    vector<int> nums1 = {5};
    vector<int> nums2 = {-1,1,8,20};
    double res = s.findMedianSortedArrays2(nums1, nums2);
    printf("result: %lf\n", res);
    vector<int> nums3 = {1,2,3,4};
    vector<int> nums4 = {-1,1,8,20, 30};
    res = s.findMedianSortedArrays2(nums3, nums4);
    printf("result: %lf\n", res);
    return 0;
}