/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 01:45:49 by napark            #+#    #+#             */
/*   Updated: 2021/12/30 00:03:09 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "parser_utils.h"

int	set_tok_type_pipe(t_par_tok *par_tok, t_iter *iter)
{
	par_tok->redir_type[is_pipe] = true;
	iter[lex]++;
	iter[par]++;
	if (init_curr_par_tok() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	get_curr_par_tok()->redir_type[is_pipe] = true;
	return (EXIT_BREAK);
}

/**
 * @brief  Gets subshell token for current parser token
 * @note   Helper function of get_special_tok
 * @param  *iter: 
 * @retval int to indicate success or failure
 */
int	get_subshell_tok(t_iter *iter)
{
	char		*lex_tok;
	t_par_tok	*par_tok;

	if (init_curr_par_tok() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	lex_tok = get_curr_lex_tok();
	par_tok = get_curr_par_tok();
	par_tok->cmd_size++;
	par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size);
	if (par_tok->cmd == NULL)
		return (EXIT_FAILURE);
	par_tok->cmd[iter[cmd]] = ft_strdup(lex_tok);
	if (par_tok->cmd[iter[cmd]] == NULL)
		return (EXIT_FAILURE);
	iter[cmd]++;
	par_tok->type = subshell;
	iter[lex]++;
	return (EXIT_BREAK);
}

bool	is_quote_token(char *lex_tok)
{
	if (ft_strchr(lex_tok, '\'') || ft_strchr(lex_tok, '\"'))
		return (true);
	return (false);
}

bool	is_redir_token(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (true);
	}
	if (ft_strlen(lex_tok) == 1)
	{
		if (ft_strchr(lex_tok, '<') || ft_strchr(lex_tok, '>'))
			return (true);
		if (ft_strchr(lex_tok, '|'))
			return (true);
	}
	return (false);
}

bool	is_special_token(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||"))
			return (true);
	}
	return (false);
}
