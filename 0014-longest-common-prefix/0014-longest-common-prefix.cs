public class Solution {
    public string LongestCommonPrefix(string[] strs) {
        if (strs.Length == 0) {
            return "";
        }

        string model = strs[0];
        char[] arr = new char[model.Length];
        int i = 0;

        for (; i < model.Length; ++i) {
            bool allMatching = true;

            for (int j = 1; j < strs.Length; ++j) {
                string curr = strs[j];

                if (i >= curr.Length || curr[i] != model[i]) {
                    allMatching = false;
                    break;
                }
            }

            if (allMatching) {
                arr[i] = model[i];
            } else {
                break;
            }
        }
        
        return new string(arr, 0, i);
    }
}