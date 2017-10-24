--1
-- create type region as enum ('Nizhegorodskiy','Kanavinskiy','Avtozavodskiy','Sovetskiy','Sormovskiy','Moskovskyi','Leninskiy','Priokskiy');
-- create table exchange_machine (id integer primary key check (id > 0), specification varchar(32) not null check (upper(specification) = specification), address region not null, insurance_fee smallint not null check (insurance_fee >= 0 and insurance_fee <= 100));
-- create table bank (id integer primary key check (id > 0), name varchar(32) not null unique, address region not null, commission smallint not null check (commission >= 0 and commission <= 100));
-- create table currency_type (id integer primary key check (id > 0), name varchar(32) unique not null, exchange_rate float not null check (exchange_rate > 0), maximum_sales_volume bigint not null check (maximum_sales_volume >= 0));
-- create type dayofweek as enum ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday');
-- create table exchange (registration_number integer primary key check(registration_number > 0), day dayofweek not null, machine integer not null, bank_addressee integer not null, currency integer not null, quantity integer not null check (quantity > 0), value integer not null, foreign key (machine) references exchange_machine(id), foreign key (bank_addressee) references bank(id), foreign key (currency) references currency_type(id));

--2
-- insert into exchange_machine (id,specification,address,insurance_fee) values 
--   (1, 'UF123-01', 'Nizhegorodskiy',2),
--   (2, 'GD341-17', 'Kanavinskiy', 2),
--   (3, 'UF232-10', 'Nizhegorodskiy', 1),
--   (4, 'UF100-12', 'Avtozavodskiy', 2),
--   (5, 'GD341-17', 'Sovetskiy', 1),
--   (6, 'UF232-10', 'Sormovskiy', 2);

-- insert into bank (id,name,address,commission) values
--   (1, 'NBD-Bank', 'Nizhegorodskiy', 12),
--   (2, 'Sberegatelniy', 'Nizhegorodskiy', 10),
--   (3, 'RTB-Bank', 'Priokskiy', 12),
--   (4, 'Kanavino bank', 'Kanavinskiy', 11),
--   (5, 'Strahovoy', 'Sovetskiy', 14);

-- insert into currency_type (id,name,exchange_rate,maximum_sales_volume) values
--   (1, 'US dollar', 24.5, 2000000),
--   (2, 'Swedish Krone', 21, 300000),
--   (3, 'Swiss Guilder', 17, 700000),
--   (4, 'Ukrainian Hryvnia', 0.7, 2000),
--   (5, 'German Mark', 30, 1000000),
--   (6, 'Austrian Krone', 21, 800000),
--   (7, 'Polish Zloty', 12, 200000);

-- insert into exchange (registration_number,day,machine,bank_addressee,currency,quantity,value) values
--   (38512, 'Monday', 1, 2, 7, 100, 1200),
--   (38513, 'Monday', 1, 5, 1, 200, 10000),
--   (38514, 'Monday', 2, 5, 1, 360, 18000),
--   (38515, 'Monday', 3, 5, 6, 50, 1150),
--   (38516, 'Monday', 5, 5, 3, 100, 1700),
--   (38517, 'Tuesday', 1, 1, 3, 50, 850),
--   (38518, 'Tuesday', 2, 3, 1, 70, 3500),
--   (38519, 'Tuesday', 4, 3, 3, 200, 3400),
--   (38520, 'Wednesday', 1, 2, 2, 50, 1150),
--   (38521, 'Wednesday', 2, 5, 1, 200, 10000),
--   (38522, 'Wednesday', 3, 2, 7, 10, 120),
--   (38523, 'Wednesday', 4, 1, 5, 100, 3000),
--   (38524, 'Thursday', 2, 5, 4, 10000000, 7000),
--   (38525, 'Friday', 1, 2, 1, 300, 15000),
--   (38526, 'Friday', 1, 3, 6, 100, 2100),
--   (38527, 'Friday', 5, 1, 4, 2000000, 14000),
--   (38528, 'Friday', 1, 4, 1, 300, 15000);

-- 3
-- select * from exchange_machine;
-- select * from bank;
-- select * from currency_type;
-- select * from exchange;

-- 4
-- select distinct specification from exchange_machine;
-- select distinct address from exchange_machine;
-- select distinct name from currency_type;

-- 5
-- select specification,address from exchange_machine where insurance_fee >= 2;
-- select name,commission from bank where commission > 10 and address != 'Kanavinskiy' order by commission;
-- select name from bank where address = 'Kanavinskiy';

-- 6
-- select exchange.registration_number, exchange.day, exchange_machine.specification, currency_type.name, exchange.value from exchange, exchange_machine, currency_type where exchange.machine = exchange_machine.id and exchange.currency = currency_type.id order by exchange_machine.specification, exchange.value desc;
-- select exchange.day, currency_type.name, exchange.quantity from exchange, currency_type where exchange.currency = currency_type.id;

--7
-- select distinct bank.name from exchange inner join exchange_machine on exchange.machine = exchange_machine.id inner join bank on exchange.bank_addressee = bank.id where bank.address != exchange_machine.address and exchange_machine.insurance_fee < 3 and exchange.day <='Wednesday';
-- select distinct exchange_machine.id, exchange_machine.specification from exchange_machine inner join bank on exchange_machine.address = bank.address;
-- select distinct bank.name from exchange inner join bank on exchange.bank_addressee = bank.id group by bank.name having SUM(exchange.value) > 5000;
-- select distinct currency_type.name from exchange inner join currency_type on exchange.currency = currency_type.id group by currency_type.name where value > 2000;

--8
-- update exchange as e set value = cast(e.value + (e.value * (select exchange_machine.insurance_fee from exchange inner join exchange_machine on exchange.machine = exchange_machine.id where e.registration_number = exchange.registration_number) / 100) + (e.value * (select bank.commission from exchange inner join bank on exchange.bank_addressee = bank.id where e.registration_number = exchange.registration_number) / 100) as integer);

--9
-- alter table exchange add bank_commission integer not null default 0;
-- update exchange as e set bank_commission = (select bank.commission from exchange inner join bank on exchange.bank_addressee = bank.id where e.registration_number = exchange.registration_number); 

--10
-- select distinct bank.name from (exchange inner join bank on exchange.bank_addressee = bank.id inner join exchange_machine on exchange.machine = exchange_machine.id) where bank.address not in (exchange_machine.address) and exchange.day in ('Monday','Tuesday','Wednesday') and exchange_machine.insurance_fee in (select insurance_fee from exchange_machine where insurance_fee < 3);
-- select bank.name from bank where bank.id in (select exchange.bank_addressee from exchange group by bank_addressee having sum(value) > 5000);

-- select * from exchange_machine where id not in (select id from exchange_machine where specification like '%UF%'); 

-- select name from bank where address not in ('Kanavinskiy');

--11
