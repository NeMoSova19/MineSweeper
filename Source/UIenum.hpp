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
	InOneLine, // � ���� ����� (�� �������� ������ �� ��� ������� � �����? � ��������� ������������ ��� �����)
	InfiniteWrap, // ����������� �������
	Bounded // ������������ �����
};
enum class EndLastWrap {
	DeleteLastWord,
	DeleteLastLetter
};
