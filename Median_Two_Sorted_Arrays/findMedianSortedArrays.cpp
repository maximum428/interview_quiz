double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int> nums3(nums1);
    nums3.insert(nums3.end(), nums2.begin(), nums2.end());
    auto odd = nums3.size() % 2, magic = nums3.size() / 2;
    std::sort(nums3.begin(), nums3.end());
    return (odd ? nums3[magic] : (double)(nums3[magic-1] + nums3[magic]) / 2);
}
