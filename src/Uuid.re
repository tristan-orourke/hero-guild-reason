let lastId = ref(0);

let heroId = (): string => {
  lastId := lastId^ + 1;
  "hero:" ++ string_of_int(lastId^);
};

let questId = (): string => {
  lastId := lastId^ + 1;
  "quest:" ++ string_of_int(lastId^);
};