class Solution {
    public String countAndSay(int n) {
        String str = "1";
        //if (n < 2) throw new IllegalArgumentException("Error");
        
        while (n > 1) {
            int count = 0;
            char c = str.charAt(0);
            StringBuilder pre = new StringBuilder();
            for (int i = 0; i <= str.length(); i++) {
                if (i != str.length() && str.charAt(i) == c) {
                    count++;
                } else {
                    pre.append(count);
                    pre.append(c); //str.charAt(i - 1));
                    if (i != str.length()) {
                        c = str.charAt(i);
                        count = 1;
                    }
                }
            }
            str = pre.toString();
            n--;
        }
        return str;
    }
}
