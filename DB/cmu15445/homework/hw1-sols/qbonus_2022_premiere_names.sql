-- Concatenate the dubbed names for each TV series premiering in 2022 with a
-- rating equal to or above a 9.0.

WITH t AS (
      SELECT
            titles.primary_title as name,
            akas.title as dubbed,
            (titles.primary_title = akas.title) AS starter
      FROM
            titles
            INNER JOIN akas ON titles.title_id = akas.title_id
            INNER JOIN ratings ON titles.title_id = ratings.title_id
            WHERE titles.premiered = 2022 AND titles.type = 'tvSeries' AND ratings.rating >= 9.0
            GROUP BY titles.primary_title, akas.title
            ORDER BY titles.primary_title ASC, starter DESC, akas.title ASC
),
r AS (
      select t.name as name, row_number() over (order by t.name asc) as seqnum, t.dubbed as dubbed
      from t
),
dub_cte AS (
      SELECT
            r.name, r.seqnum, r.dubbed
      FROM
            r
      WHERE
            r.name = r.dubbed
      UNION ALL
      SELECT
            r.name, r.seqnum,  c.dubbed || ', ' || r.dubbed
      FROM
            r INNER JOIN dub_cte c ON r.name = c.name AND r.seqnum = c.seqnum + 1
)
SELECT name, MAX(dubbed) FROM dub_cte
GROUP BY name
;

-- Topics: Recursive CTE with enforced monotonic ordering

-- Answer:
-- A Ponte - The Bridge Brasil|A Ponte - The Bridge Brasil
-- Angel|Angel
-- Apoy sa langit|Apoy sa langit, Apoy Sa Langit
-- Badlee|Badlee
-- Bravehearts|Bravehearts
-- Gangs of Puri|Gangs of Puri, Ganga of Puri
-- House of the Dragon|House of the Dragon, A Casa do Dragão, A Guerra dos Tronos: A Casa do Dragão, Dom smoka, Game of Thrones: A Casa do Dragão, Gia Tộc Rồng, La Casa del Dragón, La casa del dragón, Rod draka, Ród smoka, Sárkányok háza, Zmajeva kuća, Дом Дракона, Домът на дракона, Дім Дракона, Кућа змаја, בית הדרקון, آل التنين, ハウス・オブ・ザ・ドラゴン, 龍族前傳, 하우스 오브 드래곤
-- Irene's Work & Holiday|Irene's Work & Holiday
-- Jack dan Danil|Jack dan Danil
-- Mahapaap|Mahapaap
-- My Pack Life|My Pack Life, Minha Vida Animal
-- NCR Days|NCR Days
-- Payback|Payback
-- Royal Blood|Royal Blood
-- Selección Argentina, la serie - Camino a Qatar|Selección Argentina, la serie - Camino a Qatar, Argentine National Team, Road to Qatar, Seleção Argentina: A Série - Rumo a Catar
-- The Love Proposal|The Love Proposal, Wayla Kammathep
-- The Story Behind the Story|The Story Behind the Story, The Story Behind the Story with Mike Rowe, The Way I Heard It with Mike Rowe
-- The War of Flowers|The War of Flowers
-- Throne of Seal|Throne of Seal, Shen Yin Wangzuo
-- Two Conjectures About Marriage|Two Conjectures About Marriage
