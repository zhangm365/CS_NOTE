-- Concatenate all the unique titles for the TV Series "House of the Dragon"
-- as a string of comma-separated values in alphabetical order of the titles.

-- Detail:
-- Find all the unique dubbed titles for the new TV show "House of the Dragon"
-- and order them alphabetically. Print a single string containing all these
-- titles separated by commas.
--
-- Hint: You might find Recursive CTEs useful.
-- NOTE: Two titles are different even if they differ only in capitalization.

with p as (
      select titles.primary_title as name, akas.title as dubbed
      from titles
      inner join akas on titles.title_id = akas.title_id
      where titles.primary_title = "House of the Dragon" AND titles.type = 'tvSeries'
      group by titles.primary_title, akas.title
      order by akas.title
),
c as (
      select row_number() over (order by p.name asc) as seqnum, p.dubbed as dubbed
      from p
),
flattened as (
      select seqnum, dubbed
      from c
      where seqnum = 1
      union all
      select c.seqnum, f.dubbed || ', ' || c.dubbed
      from c join
            flattened f
            on c.seqnum = f.seqnum + 1
)
select dubbed from flattened
order by seqnum desc limit 1;

-- Topics: Recursive CTE

-- Answer:
-- A Casa do Dragão, A Guerra dos Tronos: A Casa do Dragão, Dom smoka, Game of Thrones: A Casa do Dragão, Gia Tộc Rồng, House of the Dragon, La Casa del Dragón, La casa del dragón, Rod draka, Ród smoka, Sárkányok háza, Zmajeva kuća, Дом Дракона, Домът на дракона, Дім Дракона, Кућа змаја, בית הדרקון, آل التنين, ハウス・オブ・ザ・ドラゴン, 龍族前傳, 하우스 오브 드래곤
