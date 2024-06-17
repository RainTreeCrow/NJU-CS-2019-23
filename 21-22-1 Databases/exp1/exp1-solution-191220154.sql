-- 姓名：张涵之
-- 学号：191220154
-- 提交前请确保本次实验独立完成，若有参考请注明并致谢。

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q1
select count(*) as speciesCount from (
	select distinct id from Species where description like '%this%'
) ThisSpecies;
-- END Q1

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q2
select username, sum(power) as totalPhonemonPower from (
	select SelectedPlayer.id as id, 
		SelectedPlayer.username as username,
		Phonemon.power as power
    from Phonemon, (select * from Player
		where username = 'Cook' or username = 'Hughes') as SelectedPlayer
	where SelectedPlayer.id = Phonemon.player
) PlayerPhonemon group by id;
-- END Q2

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q3
select title, count(player) as numberOfPlayers from (
	select Team.id as id, Team.title as title, Player.id as player
    from Team, Player
    where Team.id = Player.team
) TeamPlayer group by id order by numberOfPlayers desc;
-- END Q3

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q4
select Species.id as idSpecies, Species.title as title from Type, Species
where Type.title = 'grass' and (Species.type1 = Type.id or Species.type2 = Type.id);
-- END Q4

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q5
select id as idPlayer, username from Player where id not in (
	select distinct player from Purchase, Item
    where Purchase.item = Item.id and Item.type = 'F'
);
-- END Q5

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q6
select Player.level as level,
sum(SpentEachPlayer.totalSpent) as totalAmountSpentByAllPlayersAtLevel from Player, (
	select PurchaseItem.buyer as player, sum(PurchaseItem.cost) as totalSpent from (
		select Purchase.player as buyer, Purchase.Quantity * Item.price as cost
        from Purchase, Item
        where Purchase.item = Item.id
	) PurchaseItem group by buyer
) SpentEachPlayer
where Player.id = SpentEachPlayer.player
group by Player.level order by totalAmountSpentByAllPlayersAtLevel desc;
-- END Q6

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q7
select Item.id as item, Item.title as title, CountPurchase.times as numTimesPurchased
from Item, (
	select item, count(item) as times from Purchase group by item
    having times = (select max(_times) from (
		select count(item) as _times from Purchase group by item
	) temp)
) CountPurchase
where Item.id = CountPurchase.item;
-- END Q7

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q8
select id as playerID, username, cnt as numberDistinctFoodItemsPurchased from Player, (
	select Purchase.player as player, count(distinct Item.id) as cnt from Purchase, Item
    where Item.id = Purchase.item and Item.type = 'F'
    group by Purchase.player having count(distinct Item.id) = (
		select count(distinct id) from Item where type = 'F'
	)
) PurchasePlayer
where id = player;
-- END Q8

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q9
select count(distance) as numberOfPhonemonPairs, distance as distanceX from (
	select round(sqrt(power(P1.latitude - P2.latitude, 2)
		+ power(P1.longitude - P2.longitude, 2)) * 100, 2)
    as distance from Phonemon P1, Phonemon P2
	where P1.id < P2.id
) diff where distance = (select 
	min(_distance) from (select 
		round(sqrt(power(P1.latitude - P2.latitude, 2)
			+ power(P1.longitude - P2.longitude, 2)) * 100, 2)
		as _distance from Phonemon P1, Phonemon P2
        where P1.id < P2.id
	) temp
);
-- END Q9

-- ____________________________________________________________________________________________________________________________________________________________________________________________________________
-- BEGIN Q10
select Player.username as username, Type.title as typeTitle from (
	select Type.id type, count(distinct Species.id) kind from Species, Type
	where Species.type1 = Type.id or Species.type2 = Type.id
    group by Type.id) as TypeGroup, (
	select player _player, _type, count(distinct species) _kind from Phonemon, (
		select Species.id as _species, Type.id as _type from Species, Type
        where Species.type1 = Type.id or Species.type2 = Type.id
		) as TypeSpecies
    where species = _species and player is not NULL
    group by _player, _type) as PlayerGroup,
    Player, Type
where kind = _kind and type = _type and Player.id = _player and Type.id = _type;
-- END Q10