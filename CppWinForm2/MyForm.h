#pragma once
#include "Transform.h"
#include "function.h"
#include "Clip.h"
namespace TASK5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Collections::Generic::List<line> lines;

		float left, right, top, bottom;
		float Wcx, Wcy, Wx, Wy;
		float Vcx, Vcy, Vx, Vy;
		bool drawNames;

	private: int K, L;
	float OldVcx, OldVcy, OldVx, OldVy;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(220, 150);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		Rectangle rect = Form::ClientRectangle;

		left = 50;
		right = 50;
		top = 50;
		bottom = 50;

		Vcx = -5;
		Vcy = -5;
		Vx = 10;
		Vy = 10;

		OldVcx = Vcx, OldVcy = Vcy, OldVx = Vx, OldVy = Vy;

		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;

		K = 9; 
		L = 9;

		drawNames = false;
		lines.Clear();
		unit(T);
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		System::Drawing::Graphics^ g = e->Graphics;
		g->Clear(Color::White);

		Rectangle rect = Form::ClientRectangle;
		System::Drawing::Pen^ rectPen = gcnew Pen(Color::Pink);
		rectPen->Width = 2;
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

		System::Drawing::Pen^ linePen = gcnew Pen(Color::Green);
		linePen->Width = 1;

		float lengthx = Wx / (L + 1);
		float lengthy = Wy / (K + 1);
		float xk1 = left, yk1 = bottom, xk2, yk2;

		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

		for (int i = 0; i < L; i++)
		{
			xk1 += lengthx;
			yk1 = bottom;
			xk2 = xk1;
			yk2 = bottom + Wy;

			g->DrawLine(linePen, xk1, yk1, xk2, yk2);

			float vx = ((xk1 - Wcx) / Wx) * Vx + Vcx;

			std::stringstream s;
			s.precision(3);
			s << vx;
			std::string valuex;
			s >> valuex;
			g->DrawString(gcnew String(valuex.c_str()), drawFont, drawBrush, xk2 - 5, yk2 + 5);
		}

		for (int i = 0; i < K; i++)
		{
			xk1 = left;
			yk1 += lengthy;
			xk2 = left + Wx;
			yk2 = yk1;
			g->DrawLine(linePen, xk1, yk1, xk2, yk2);

			float vy = Vcy - ((yk1 - Wcy) / Wy) * Vy;

			std::stringstream s;
			s.precision(3);
			s << vy;
			std::string valuey;
			s >> valuey;
			g->DrawString(gcnew String(valuey.c_str()), drawFont, drawBrush, xk2 + 5, yk2 - 5);
		}

		bool visible1 = false, visible2 = false;

		float y = 0, y1 = 0, y2 = 0, x = Vcx, x1, x2 = 0;

		System::Drawing::Pen^ grPen = gcnew Pen(Color::Red);
		grPen->Width = 3;

		for (x1 = Wcx; x1 < Wcx + Wx; x1++)
		{
			point a, b;
			a.x = x1;
			b.x = x1 + 1;

			if (fexists(x))
			{
				visible1 = true;
				y = f(x);
				y1 = Wcy - ((y - Vcy) / Vy) * Wy;
				a.y = y1;
			}
			else visible1 = false;

			x = ((x1 + 1 - Wcx) / Wx) * Vx + Vcx;

			if (fexists(x))
			{
				visible2 = true;
				y = f(x);
				y2 = Wcy - ((y - Vcy) / Vy) * Wy;
				b.y = y2;
			}
			else visible2 = false;

			if (fexists(x))
			{
				visible2 = true;
				y = f(x);
				y2 = Wcy - ((y - Vcy) / Vy) * Wy;
				b.y = y2;
			}
			else visible2 = false;

			point pmin, pmax;
			pmin.x = left;
			pmin.y = top;
			pmax.x = rect.Width - right;
			pmax.y = rect.Height - bottom;

			if (visible1 && visible2)
			{
				if (Clip(a, b, pmin, pmax))
					g->DrawLine(grPen, a.x, a.y, b.x, b.y);
			}
		}
	}

	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
	{
		Rectangle rect = Form::ClientRectangle;
		float LENGTH;
		switch (e->KeyCode)
		{
		case Keys::I: 
			LENGTH = Vy; 
			Vy /= 1.1;
			Vcy += (LENGTH - Vy) / 2; 
			break;
		case Keys::O: 
			LENGTH = Vy; 
			Vy *= 1.1;
			Vcy += (LENGTH - Vy) / 2; 
			break;
		case Keys::K: 
			LENGTH = Vx; 
			Vx /= 1.1;
			Vcx += (LENGTH - Vx) / 2;
			break;
		case Keys::L: 
			LENGTH = Vx; 
			Vx *= 1.1;
			Vcx += (LENGTH - Vx) / 2; 
			break;

		case Keys::W: 
			Vcy -= (Vy / Wy);
			break;
		case Keys::S: 
			Vcy += (Vy / Wy);
			break;
		case Keys::A: 
			Vcx += (Vx / Wx);
			break;
		case Keys::D: 
			Vcx -= (Vx / Wx);
			break;

		case Keys::T:  
			Vcy -= 20 * (Vy / Wy);
			break;
		case Keys::G:  
			Vcy += 20 * (Vy / Wy);
			break;
		case Keys::F:  
			Vcx += 20 * (Vx / Wx);
			break;
		case Keys::H: 
			Vcx -= 20 * (Vx / Wx);
			break;

		case Keys::Q: 
			L++;
			break;
		case Keys::E: 
			if (L > 1)
				L--;
			break;
		case Keys::Z: 
			K++;
			break;
		case Keys::C: 
			if (K > 1) 
				K--;
			break;

		case Keys::Escape:
			K = 5;
			L = 5;
			Vcx = OldVcx;
			Vcy = OldVcy;
			Vx = OldVx;
			Vy = OldVy;
			break;
		}
		this->Refresh();
	}

private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
	float oldWx = Wx, oldWy = Wy;
	Wcx = left;
	Wcy = Form::ClientRectangle.Height - bottom;
	Wx = Form::ClientRectangle.Width - left - right;
	Wy = Form::ClientRectangle.Height - top - bottom;
	this->Refresh();
}
};
}