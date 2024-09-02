class Solution:
    def isPalindrome(self, s: str) -> bool:
        sf: str = s.replace(" ", "").lower()
        sf = "".join(filter(str.isalnum, sf))
        return sf == sf[::-1]
