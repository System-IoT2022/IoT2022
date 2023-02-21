import flet as ft

def main(page: ft.Page):
    page.title = "Flet counter example"
    page.vertical_alignment = ft.MainAxisAlignment.CENTER

    btn0 = ft.ElevatedButton("switch on")
    btn1 = ft.ElevatedButton("switch off")
    slider = ft.Slider()   

    page.add(
        ft.Column(
        [        
            ft.Row(
            [                
                btn0,
                btn1
            ],
            alignment=ft.MainAxisAlignment.CENTER,
            ),
            ft.Row(
            [
                slider
            ]
            )

        ]
        )
       
    )

ft.app(target=main)