#pragma once

enum class AlignmentHorizontal
{
	Left, Center, Right, Width
};
enum class AlignmentVertical
{
	Top, Center, Down, Height
};
enum class TextRectType
{
	InOneLine, // В одну линию (мб выводить только то что влазиет в линию? и применять выравнивание для линии)
	InfiniteWrap, // Бесконечный перенос
	Bounded // Ограниченный текст
};
enum class EndLastWrap {
	DeleteLastWord,
	DeleteLastLetter
};
