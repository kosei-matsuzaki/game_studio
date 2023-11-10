#include "maps.h"

const map_info natsumatsuri = {
    .id = 3,
    .name = "Natsumatsuri",
    .difficulty = 3.0,
    .bpm = 110,
    .beat = 4,
    .bar_count = 34,
    .map = {
        { 0,0,0,0 }, // 1
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },

        { 1,0,0,0 }, // 2.君がいた
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 3.夏は遠い
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },

        { 1,1,0,0 }, // 4.夢の中
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,1,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 5
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 6.空に
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,0,0,1 }, // 7.消えてった
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 1,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 8.打ち上げ花火
        { 0,0,0.0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 9
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 10
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 11.君の髪の
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,1,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 12.香りはじけた
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 13.浴衣姿が
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 14.まぶしすぎて
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 15.お祭りの夜は
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,1,0,0 }, // 16. 
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 17.胸が騒いだよ
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,1,0,0 }, // 18
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 19.はぐれそうな
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,1,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 20.人ごみの中

        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 21.はなれないで
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 22.出しかけた手を
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 23.ポケットに入れて
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,1,0,0 }, // 24
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 25.握りしめていた
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,1,0,0 }, // 26
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },

        { 1,0,0,0 }, // 27.君がいた
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 28.夏は遠い
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },

        { 1,1,0,0 }, // 29.夢の中
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,1,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 30
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,0,1 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,1,0 }, // 31.空に
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 0,0,0,1 }, // 32.消えてった
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,1,0 },
        { 0,1,0,0 },
        { 1,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 1,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 33.打ち上げ花火
        { 0,0,0.0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,1,1 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 0,0,0,0 },

        { 1,0,0,1 }, // 34
        { 0,0,0.0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 0,0,0,0 },
    },
};