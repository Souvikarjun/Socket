class Solution(object):
	def isMatch(self, s, p):
		"""
		:type s: str
		:type p: str
		:rtype: bool
		"""
		i, j = len(s)-1, len(p)-1
		return self.backtrack({}, s, p, i, j)

	def backtrack(self, cache, s, p, i, j):
		key = (i,j)
		if key in cache:
			return cache[key]