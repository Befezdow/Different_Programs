create type region as enum ('Nizhegorodskiy','Kanavinskiy','Avtozavodskiy','Sovetskiy','Sormovskiy','Moskovskyi','Leninskiy','Priokskiy');
create table exchange_machine (id integer primary key check (id > 0), specification varchar(32) not null check (upper(specification) = specification), address region not null, insurance_fee smallint not null check (insurance_fee >= 0 and insurance_fee <= 100));
create table bank (id integer primary key check (id > 0), name varchar(32) not null unique, address varchar(32) not null, commission smallint not null check (commission >= 0 and commission <= 100));
create table currency_type (id integer primary key check (id > 0), name varchar(32) unique not null, exchange_rate float not null check (exchange_rate > 0), maximum_sales_volume bigint not null check (maximum_sales_volume >= 0));
create type dayofweek as enum ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday');
create table exchange (registration_number integer primary key check(registration_number > 0), day dayofweek not null, machine integer not null, bank_addressee integer not null, currency integer not null, quantity integer not null check (quantity > 0), value integer not null, foreign key (machine) references exchange_machine(id), foreign key (bank_addressee) references bank(id), foreign key (currency) references currency_type(id));

insert into exchange_machine (id,specification,address,insurance_fee) values 
  (1,'UF123-01','Nizhegorodskiy',2),
  (2,'GD341-17','Kanavinskiy', 2),
  (3,'UF232-10','Nizhegorodskiy', 1),
  (4,'UF100-12','Avtozavodskiy', 2),
  (5,'GD341-17','Sovetskiy', 1),
  (6,'UF232-10','Sormovskiy', 2);