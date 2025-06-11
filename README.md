# Opis projektu

**ReactorBorn** to dwuwymiarowa gra akcji z widokiem z góry, inspirowana strukturą poziomów znaną z *The Binding of Isaac*. Gracz przemierza proceduralnie generowane pomieszczenia, walczy z różnymi przeciwnikami i rozwija swoją postać dzięki klasom oraz ulepszeniom. Styl gry łączy elementy roguelike, dynamicznej walki i taktycznej eksploracji.

## Funkcje

- **Wybór klasy postaci na początku rozgrywki**, każda z unikalnymi właściwościami:
  - **Berserk** – brak limitu żyć
  - **Sprinter** – 1.5× prędkości ruchu
  - **Devastator** – 2× obrażenia
  - **Lucky Man** – 100% szansy na loot z wrogów oraz 10 monet na start

- **Ulepszenia postaci** dostępne za monety:
  - Zmniejszenie czasu przeładowania
  - Zwiększenie prędkości gracza
  - Spowolnienie wrogów
  - Spowolnienie pocisków wrogów
  - Zwiększenie maksymalnego zdrowia
  - Uleczenie
    
  *Każdy kolejny zakup zwiększa koszt ulepszenia*

- **Minimapa**, która pokazuje:
  - **Zielone pola** – odwiedzone poziomy
  - **Czarne pola** – nieodwiedzone, ale sąsiadujące z odwiedzonymi
  - **Czerwone pole** – aktualna pozycja gracza

- **Losowa struktura mapy**:
  - Rozmieszczenie pomieszczeń generowane losowo
  - Każdy poziom dobierany jest na podstawie **gotowego szablonu**
  - Algorytm gwarantuje, że **wszystkie pokoje są dostępne i połączone**

- **4 typy przeciwników**, każdy z odmiennym zachowaniem:
   - **Wieżyczka** – nieruchomy przeciwnik, który regularnie strzela w czterech kierunkach (góra, dół, lewo, prawo)
   - **Człowiek** – porusza się i strzela w stronę gracza; jego pociski zatrzymują się na przeszkodach
   - **Robot** – powolny przeciwnik z dużą ilością życia, aktywuje się z opóźnieniem i prowadzi ostrzał w stronę gracza
   - **Dron** – szybki, latający wróg, który może przelatywać nad przeszkodami i strzelać do gracza z każdej pozycji


- **Losowy poziom ze skrzynkami**, w których znaleźć można:
  - Monety
  - Podwójne monety
  - Uleczenie
  - Zwiększenie maksymalnego zdrowia

- **Animacje dla niemal każdego elementu gry** – poruszające się dekoracje, żywe postacie i przeciwnicy

- **Pixelartowa stylistyka i dynamiczna oprawa graficzna**, budująca atmosferę eksperymentu i zagrożenia

## Jak uruchomić projekt z konsoli (CMD)

1. Otwórz konsolę (CMD) w katalogu głównym projektu (tam, gdzie znajduje się plik `CMakeLists.txt`).

2. Utwórz folder do budowania i przejdź do niego:

   ```bash
   mkdir build
   cd build
   ```

3. Wygeneruj pliki projektu za pomocą CMake:

   ```bash
   cmake ..
   ```

4. Zbuduj projekt:

   ```bash
   cmake --build .
   ```

5. Uruchom program:

   ```bash
   ReactorBorn.exe
   ```

## Wymagania

- Kompilator C++ (GCC, Clang lub MSVC)
- CMake 3.16 lub nowszy
- System operacyjny: Windows / Linux / macOS

## Autor

Jędrzej Nowakowski
