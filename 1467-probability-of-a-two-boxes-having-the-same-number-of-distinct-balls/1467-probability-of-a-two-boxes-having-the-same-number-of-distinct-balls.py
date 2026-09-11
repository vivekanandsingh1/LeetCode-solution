class Solution(object):
    def getProbability(self, balls):
        k = len(balls)
        n = sum(balls) // 2
        self.total = 0.0
        self.valid = 0.0

        def comb(a, b):
            if b < 0 or b > a:
                return 0
            result = 1
            for i in range(b):
                result = result * (a - i) // (i + 1)
            return result

        def dfs(i, box1_count, box2_count, box1_colors, box2_colors, ways):
            if i == k:
                if box1_count == n:
                    self.total += ways
                    if box1_colors == box2_colors:
                        self.valid += ways
                return
            for x in range(balls[i] + 1):
                y = balls[i] - x
                if box1_count + x > n or box2_count + y > n:
                    continue
                new_ways = ways * comb(balls[i], x)
                dfs(
                    i + 1,
                    box1_count + x,
                    box2_count + y,
                    box1_colors + (1 if x > 0 else 0),
                    box2_colors + (1 if y > 0 else 0),
                    new_ways
                )

        dfs(0, 0, 0, 0, 0, 1.0)
        return self.valid / self.total