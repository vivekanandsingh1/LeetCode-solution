# Write your MySQL query statement below
SELECT ip, COUNT(*) AS invalid_count
FROM (
    SELECT 
        ip,
        LENGTH(ip) - LENGTH(REPLACE(ip, '.', '')) AS dots,
        SUBSTRING_INDEX(ip, '.', 1) AS o1,
        SUBSTRING_INDEX(SUBSTRING_INDEX(ip, '.', 2), '.', -1) AS o2,
        SUBSTRING_INDEX(SUBSTRING_INDEX(ip, '.', 3), '.', -1) AS o3,
        SUBSTRING_INDEX(ip, '.', -1) AS o4
    FROM logs
) t
WHERE dots <> 3
   OR o1 > 255 OR o2 > 255 OR o3 > 255 OR o4 > 255
   OR (LENGTH(o1) > 1 AND o1 LIKE '0%')
   OR (LENGTH(o2) > 1 AND o2 LIKE '0%')
   OR (LENGTH(o3) > 1 AND o3 LIKE '0%')
   OR (LENGTH(o4) > 1 AND o4 LIKE '0%')
GROUP BY ip
ORDER BY invalid_count DESC, ip DESC;