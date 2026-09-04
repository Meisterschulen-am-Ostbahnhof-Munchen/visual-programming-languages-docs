# Uebung_010d_AX: Toggle-Flipflop mit SoftKey_F1 und GreenWhiteBackground

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_010d_AX`.

![Uebung_010d_AX_network](./Uebung_010d_AX_network.svg)

----

## Ziel der Übung

Statt nur direkt durchzuschalten, soll der SoftKey `F1` jetzt einen Zustand umschalten (Toggle), bei jedem Loslassen der Taste.

-----

## Beschreibung und Komponenten

Die Subapplikation `Uebung_010d_AX.SUB` ersetzt die direkte Durchschaltung aus `Uebung_010c_AX` durch ein Toggle-Flipflop.

### Funktionsbausteine (FBs)

  - **`SoftKey_UP_F1`**: `isobus::UT::io::Softkey::Softkey_IE`, ausgelöst durch das Ereignis `SK_RELEASED` (reagiert erst beim Loslassen der Taste, nicht beim Drücken).
  - **`AX_T_FF`**: Toggle-Flipflop-Adapter. Jedes Taktereignis an `CLK` kehrt den Ausgangszustand `Q` um.
  - **`AX_SPLIT_2`**: Verteilt das Adaptersignal von `AX_T_FF.Q` sowohl an den Ausgang `Q1` als auch an den Feedback-Baustein.
  - **`DigitalOutput_Q1`**: Ausgabe (Lampe), `Output_Q1`.
  - **`GreenWhiteBackground_AX`**: SubApp aus `MyLib::sys`, steuert das Aussehen des Softkeys `F1` auf dem Terminal (Grün = Aktiv, Weiß = Inaktiv).

-----

## Funktionsweise

1.  Der Nutzer lässt den SoftKey `F1` los; `SoftKey_UP_F1` löst das Ereignis `IND` aus.
2.  `AX_T_FF` kehrt seinen internen Zustand `Q` um (aus AN wird AUS, aus AUS wird AN).
3.  `AX_SPLIT_2` verteilt den neuen Zustand an `DigitalOutput_Q1` (physischer Ausgang) und `GreenWhiteBackground_AX` (Softkey-Hintergrundfarbe).

Im Gegensatz zu `Uebung_010c_AX`, wo der Ausgang nur während des Tastendrucks aktiv ist, bleibt der Zustand hier bis zum nächsten Loslassen der Taste erhalten.
