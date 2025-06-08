// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PorschePlayerController.h"
#include "Cars/PorscheCar.h"
#include "UI/PorscheUI.h"


APraktykiGameModeBase::APraktykiGameModeBase()
{
	DefaultPawnClass = APorscheCar::StaticClass();
	PlayerControllerClass = APorschePlayerController::StaticClass();
    HUDClass = UPorscheUI::StaticClass();
}

void APraktykiGameModeBase::BeginPlay()
{
    // Resetowanie stanu gry na początku poziomu
    CurrentLapsCompleted = 0;
    CurrentRaceTime = 0.0f;
    BestLapTime = 0.0f; // Resetowanie najlepszego czasu

    UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        CurrentRaceModeType = GameInstance->SelectedRaceMode;

        if (CurrentRaceModeType == ERaceMode::RM_Training)
        {
             
            TargetLaps = 1;     // Trening zawsze 1 okrążenie
            TargetMaxRaceTime = 0.0f;   // Trening brak limitu czasowego
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Training. Target Laps: %d, No time limit."), TargetLaps);  // Ustawiamy 0.0f, a CheckGameEndConditions zignoruje to.
        }
        else if (CurrentRaceModeType == ERaceMode::RM_Race)
        {
           
            TargetLaps = GameInstance->NumberOfLaps;     // Wyścig liczba okrążeń z menu
            TargetMaxRaceTime = 0.0f;   // Wyścig brak limitu czasowego 

            // Czas będzie mierzony, ale nie będzie kończył gry.
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Race. Target Laps: %d, Time will be measured, but no time limit."), TargetLaps);
        }
        else
        {
            // Domyślne zachowanie, jeśli tryb nie jest wybrany
            TargetLaps = 1;
            TargetMaxRaceTime = 0.0f; // Bez limitu czasu dla domyślnego trybu
            CurrentRaceModeType = ERaceMode::RM_Training;
            UE_LOG(LogTemp, Warning, TEXT("No game mode selected. Defaulting to Training with %d lap and no time limit."), TargetLaps);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PraktykiGameInstance!"));
        // Jeśli GameInstance nie został pobrany
        TargetLaps = 1;
        TargetMaxRaceTime = 0.0f;
        CurrentRaceModeType = ERaceMode::RM_Training;
    }

    // WAŻNE: W zależności od Twojego Setupu, StartGame() może być wywołane tutaj,
    // jeśli gra ma się zaczynać od razu po załadowaniu poziomu.
    // Jeśli używasz ekranu ładowania lub innej inicjalizacji, wywołaj StartGame() później.
    // StartGame();
}

void APraktykiGameModeBase::StartGame()
{
    // Logika rozpoczęcia gry: np. włączenie timera, odblokowanie inputu gracza
   // Ustawienie timera na UpdateGameTimer co 0.01 sekundy dla dokładniejszego mierzenia czasu
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &APraktykiGameModeBase::UpdateGameTimer, 0.01f, true);
    UE_LOG(LogTemp, Log, TEXT("Game Started!"));

    if (PorscheHUDUI)
    {
        UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), PorscheHUDUI);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            UE_LOG(LogTemp, Log, TEXT("Game HUD Widget created and added to viewport."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameHUDWidgetClass is not set in GameMode. HUD will not be displayed."));
    }
}

void APraktykiGameModeBase::EndGame()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle); // Zatrzymaj timer
    //UE_LOG(LogTemp, Log, TEXT("Game Ended! Player won: %s"), bPlayerWon ? TEXT("true") : TEXT("false"));

    /*Tutaj powinieneś przełączyć się na ekran podsumowania.
    if (UUserWidget* CurrentHUD = Cast<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
    {
        // Jeśli używasz PlayerController::ClientSetHUD, to będziesz musiał to zmienić
        //APorschePlayerController::ClientSetHUD;
    }*/
    // Na razie wracamy do menu głównego.
    ReturnToMainMenu();
}

void APraktykiGameModeBase::ReturnToMainMenu()
{
    UGameplayStatics::OpenLevel(this, FName("TestMap")); // Nazwa mapy menu głównego
}

void APraktykiGameModeBase::UpdateGameTimer()
{
    // Zwiększaj czas o interwał timera (0.01f)
    CurrentRaceTime += GetWorldTimerManager().GetTimerRate(GameTimerHandle);
   
    CheckGameEndConditions();
}

void APraktykiGameModeBase::CheckGameEndConditions()
{
   
    // w trybie wyścigu i treningu, co oznacza, że gra nie zakończy się z powodu upływu czasu.
    bool bLapsCompleted = (TargetLaps > 0 && CurrentLapsCompleted >= TargetLaps);

    if (bLapsCompleted)
    {
        EndGame(); // Ukończono wymagane okrążenia, koniec gry.
    }
}



