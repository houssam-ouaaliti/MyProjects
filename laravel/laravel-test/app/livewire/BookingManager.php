<?php

namespace App\Livewire;

use Livewire\Component;
use App\Models\Booking;
use Illuminate\Support\Facades\Auth;

class BookingManager extends Component
{
    public $propertyId;
    public $start_date;
    public $end_date;
    public $successMessage = '';

    public function mount($propertyId)
    {
        $this->propertyId = $propertyId;
    }

    public function save()
    {
        $this->validate([
            'start_date' => 'required|date|after_or_equal:today',
            'end_date' => 'required|date|after:start_date',
        ]);

        Booking::create([
            'user_id' => Auth::id(),
            'property_id' => $this->propertyId,
            'start_date' => $this->start_date,
            'end_date' => $this->end_date,
        ]);

        $this->successMessage = 'Réservation enregistrée !';
    }

    public function render()
    {
        return view('livewire.booking-manager');
    }
}