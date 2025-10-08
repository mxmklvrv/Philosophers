# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 17:02:31 by mklevero          #+#    #+#              #
#    Updated: 2025/10/08 19:17:51 by mklevero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
SRC_DIR = src/

HEADERS = -I ./include
PHILO_HEAD = ./include/philo.h

SRC = main.c utils.c

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
.SECONDARY: $(OBJS)

all: $(NAME)
	@printf "             IFFFFFFFPIKITOCHENIEFFFF                                    FFFFFEEFXYIDROCHENIEFFF             \n"
	@printf "              GEDDDDDIERELFFMEFFGGHHH                                    KHHHHHIIFNHQKLHEGFGGGFF             \n"
	@printf "              GFDDDDDEEFFFHFGGGJDDIHH                                    QKIEEMKJLNONNMKIHGGGGEF             \n"
	@printf "              IGDDOOFFFFFFFFFFFFFFFOH                                    OKJOOOFFFFFFFFFFFFOOOHF              \n"
	@printf "               HFDDISRRVTQQUVNJLTQNJJ                                    MLJHWWSUWURQSUSSUFDGGF              \n"
	@printf "               IHEIQRLMMRSSSNIJJJONKJ                                    MLMRSPOORUUUVPNMVTKGFG              \n"
	@printf "                HFHMMMLLRTTSULJKOUHKJ                                    NLMQRPOPRUUUSMNMQPJHG               \n"
	@printf "                HFEITRMPUUQPTUSPPQCJK                                    OLGOWSRUXVVVXNMNTNHGG               \n"
	@printf "                HGEDERRPPPPOPPNNPNDJK                                    NKGHRRRRSRQQURRSJEHFG               \n"
	@printf "                 GFDDKOPOROOPUNMOQULL                                    KJFPQQQRRRQRRPQPEFHF                \n"
	@printf "                 GFEHTPMNTRSQUKIIKSOLL                                   JIQVOPOUWTTVSOPVGGGG                \n"
	@printf "                 GGEPRLLMMMMMLJIJISNKJ                                   IISRONOOLQNNMMNUOFFH                \n"
	@printf "                 IGENRKKKNIGGIFFGGGIJJ                                   HHFFGGHKJIIILLLSMGF                 \n"
	@printf "                  GEDDDDDDDEFFH    LJH                                   GGMNHGFFEEEEEDEEFFF                 \n"
	@printf "                  HFE              LHH                                  MGFM             GFF                 \n"
	@printf "                  GFDL             LFF                                  KFFL            IFFF                 \n"
	@printf "                  HFDF        USOLKKKMQKHIIJLU                    NKIIOURQQQRS          FFFG                 \n"
	@printf "                  GFCFKJLOPPONMNPRRPPNLNOPKJJLLMNIJPT    TTJHJKINPPPQRRSSSRRRRMMMMLOOPQNHDFH                 \n"
	@printf "                  HEOKQFJNMOQQOONMJLLMPRSRRRRKJJIKKJIO  TRSSSQQQQQPQQSRNKKLLLNOGGHHHKIFRQPEF                 \n"
	@printf "                  GECGIIMLMOMKNMKJJLNNOONSTSPOFEDDDDDE   EEFFHJLMONONNNMMQSONMNOIKPPOPKGFDDF                 \n"
	@printf "                  FEDEEEEEGHIOMMNHHFEEEDDDDDDDDDDDDDDF   EEDEEEEEEEEEFFFHMPSTTPOMIHGFEEEEDD                  \n"
	@printf "                  FEDF   FEEEEEEEDDDDDDDFHI       EDEF   EEDE      LGGEEEEEEEFFFEEEEG   GDE                  \n"
	@printf "                  FEDE       FEEEG KFH IEDDCCCCFILEDEF   FEEHKIFDDDDDEK IDFKGFFFH       GDE                  \n"
	@printf "                  FEDEHKMN   GEFF  IFI          GDEDEF   FEDDEF          EF  EFFG   OLJGEDE                  \n"
	@printf "                  FEDD EEEFGHIEFE  IFH            EDEE   FFEE            FF KFGFJGGFFFF HDE                  \n"
	@printf "                  EEEE     FFEEEFL IFJ            DEEF   FFEE            FFJGFGFEFF     EEFH                 \n"
	@printf "                  EEEH        EFFJ HF             DEEE   FFEF            FFKFFHF        EEFG                 \n"
	@printf "                  EEE         EFEG GF             EEEE   EFF             FEJGFGG         EFF                 \n"
	@printf "                  EEE         FFEG FE             GEFE   FFF             FEIFGGF         EFF                 \n"
	@printf "                  EEF         GFEG                 EEH   GFG                FGGF         FFF                 \n"
	@printf "                  EEE         FFEF                 FFF   FF                 GGGF         HEF                 \n"
	@printf "                  GH          FEEF                 EFF   FF                 GGGF          F                  \n"
	@printf "                              GEEF                       GH                 GGFF                             \n"
	@printf "                              HEEG                                          GGFE                             \n"
	@printf "                               FEF                                          HHF                              \n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(PHILO_HEAD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(PHILO_HEAD)
	$(CC) $(OBJS)  $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

